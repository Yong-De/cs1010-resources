#################################
# Default SoC-PE settings (start)
#################################

umask 077
HISTSIZE=1000
ulimit -S -f 102400

alias rm="rm -i"
alias cp="cp -i"
alias mv="mv -i"

set -o noclobber

# Disable ctrl-s and ctrl-q
stty -ixon

# Add time-stamps to bash history
HISTTIMEFORMAT="%F %T"

# Immediate append to bash history upon each command
PROMPT_COMMAND="history -a"

###############################
# Default SoC-PE settings (end)
###############################
