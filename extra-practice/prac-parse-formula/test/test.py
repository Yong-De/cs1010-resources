#!/usr/bin/python

import subprocess
import os
import glob
from enum import Enum

class ASSIGNMENT_TYPE(Enum):
    FROM_SCRATCH = 1
    HOISTED = 2

DIFF_COL_WIDTH = 130
DIFF_FLAGS = F"-y --width={DIFF_COL_WIDTH}"
def pretty_print_diff(diff_out):
    
    print("Output differs from expected. :(")
    print("Expected:".ljust(DIFF_COL_WIDTH // 2 - 2), "Actual:")
    # print()
    
    
    # expected_line_start, expected_line_end = map(int, split_by_lines[3].strip("* ").split(","))
    # # print(split_by_lines[3].strip("* ").split(","))    
    # print(F"{expected_line_start}, {expected_line_end}")
    # total_expected_lines = expected_line_end - expected_line_start + 1
    # now find the differing lines
    print(diff_out, end="")
    pass

BASEDIR="test"
# TYPE = ASSIGNMENT_TYPE(1)
# TYPE = ASSIGNMENT_TYPE(2)


# now we run through all the test cases
# case_files = os.listdir(F"{BASEDIR}/test_cases/*.in")
case_files = glob.glob(F"{BASEDIR}/test_cases/*.in")
# we know they're labelled sequentially, so...
num_cases = len(case_files) // 2

# trust make to build any required executables

TYPE = os.environ['ASSIGNMENT_TYPE']

import signal
def _kill_descendants_linux(ppid: int, sig: int = signal.SIGKILL) -> None:
    """
    Linux-only best-effort: kill all descendants of ppid (for cases where the
    student program daemonized/changed session and escaped our process group).
    """
    proc_dir = "/proc"
    if not os.path.isdir(proc_dir):
        return
    children = {}
    for entry in os.listdir(proc_dir):
        if not entry.isdigit():
            continue
        pid = int(entry)
        try:
            with open(f"{proc_dir}/{pid}/stat", "r") as f:
                parts = f.read().split()
            parent = int(parts[3])  # PPID from /proc/<pid>/stat
        except Exception:
            continue
        children.setdefault(parent, []).append(pid)

    stack = children.get(ppid, [])[:]
    seen = set()
    while stack:
        cpid = stack.pop()
        if cpid in seen:
            continue
        seen.add(cpid)
        try:
            os.kill(cpid, sig)
        except Exception:
            pass
        stack.extend(children.get(cpid, []))

if TYPE == 'STANDALONE':
    # go get the executable name
    with open(F"Makefile", "r") as makefile:
        EXECUTABLE_NAME = None
        for line in makefile:
            if line[:len("TARGET = ")] == "TARGET = ":
                EXECUTABLE_NAME = line.split(" = ")[1].strip()
                break
        assert(EXECUTABLE_NAME is not None)


failed_cases = []
for case_name in case_files:
    case_prefix = case_name.split(".in")[0].split(F"{BASEDIR}/test_cases/")[1]
    with open(F"{BASEDIR}/test_cases/{case_prefix}.in", "r") as in_file, open(F"{BASEDIR}/test_cases/{case_prefix}.out", "r") as expected_file:
        print(F"=====================================================================")
        print(F"Test case file: {case_prefix}.in")
        # print(F"Input: {in_file.read()}")
        print(F"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
        print(F"Running...")
        print(F"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")

        # maybe don't capture stderr
        if TYPE == 'STUBBED':
            # TODO: change this to use diff or someting idk
            result = subprocess.run([F"./{BASEDIR}/test_bin"], stdin=in_file, capture_output=True)
        else:
            # Non-STANDALONE: run "./EXECUTABLE_NAME < case.in | diff ..."
            in_path  = f"{BASEDIR}/test_cases/{case_prefix}.in"
            out_path = f"{BASEDIR}/test_cases/{case_prefix}.out"

            try:
                # 1) Launch student executable as process-group leader
                exe_proc = subprocess.Popen(
                    [f"./{EXECUTABLE_NAME}"],
                    stdin=in_file,               # feed the .in file
                    stdout=subprocess.PIPE,      # pipe to diff
                    stderr=None,
                    text=True,
                    start_new_session=True,      # so we can killpg() on timeout
                )

                # 2) Run diff normally, reading from the student's stdout
                diff_proc = subprocess.Popen(
                    ["diff", *DIFF_FLAGS.split(), out_path, "-"],
                    stdin=exe_proc.stdout,
                    stdout=subprocess.PIPE,
                    stderr=subprocess.STDOUT,
                    text=True,
                )
                exe_proc.stdout.close()  # parent no longer needs this end

                # 3) Enforce a hard timeout on the whole pipeline via diff
                output, _ = diff_proc.communicate(timeout=5)

                if diff_proc.returncode == 0:
                    print("Success!")
                else:
                    failed_cases.append(case_name)
                    pretty_print_diff(output or "")

                # Ensure the student process is gone; if not, kill group + descendants
                try:
                    exe_proc.wait(timeout=1)
                except subprocess.TimeoutExpired:
                    try:
                        os.killpg(exe_proc.pid, signal.SIGKILL)
                    except Exception:
                        pass
                    _kill_descendants_linux(exe_proc.pid, signal.SIGKILL)
                    try:
                        exe_proc.wait(timeout=1)
                    except Exception:
                        pass

            except subprocess.TimeoutExpired:
                # Timeout: kill the student group and stop diff
                try:
                    os.killpg(exe_proc.pid, signal.SIGKILL)
                except Exception:
                    pass
                try:
                    diff_proc.kill()
                except Exception:
                    pass
                _kill_descendants_linux(exe_proc.pid, signal.SIGKILL)
                try:
                    diff_proc.communicate(timeout=1)
                except Exception:
                    pass
                try:
                    exe_proc.wait(timeout=1)
                except Exception:
                    pass
                print("Timeout!")
                failed_cases.append(case_name)



if len(failed_cases) != 0:
    print(F"Incorrect behaviour on cases:")
    for case_name in failed_cases:
        print(case_name)
    exit(1)
else:
    print("All cases passed!")
