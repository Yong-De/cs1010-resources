# To adapt this Makefile to your project:
# 1. List out the libraries you need in LIBS e.g. LIBS = gtk+-3.0
# 2. Write out the name of the file that has main, without the .c extension
# 		E.g. mini_rotate_gtk3.c holds the main function, write mini_rotate_gtk3
# Leave the rest alone, compile_flags.txt will be generated on the first make
#
# An autoconfigured .clang-format is also included by default

CC = clang
CFLAGS = -Wall -Wextra -O0 -g -MMD
LIBS = # Fill this in
LDFLAGS = `pkg-config --libs $(LIBS)`
TARGET = test
FORMAT_EXTENSIONS = c h

SRC = $(wildcard ./*.c)
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

.PHONY: all clean clean_fr format echo tidy

$(TARGET): $(OBJ)
	$(CC) @compile_flags.txt $^ -o $@_bin $(LDFLAGS) && make tidy

%.o: %.c compile_flags.txt
	$(CC) @compile_flags.txt -c $< -o $@

compile_flags.txt:
	(echo $(CFLAGS) | tr ' ' '\n'; \
		pkg-config --cflags $(LIBS) | tr ' ' '\n'	) > compile_flags.txt

tidy:
	@echo "Linting source files..."
	@find . -type f \( $(foreach ext,$(FORMAT_EXTENSIONS),-name '*.$(ext)' -o ) -false \) \
		-exec clang-tidy -quiet {} + 2> /dev/null
	@echo "Done linting!"

submit:
	./submit.sh


format:
	@echo "Formatting source files..."
	@find . -type f \( $(foreach ext,$(FORMAT_EXTENSIONS),-name '*.$(ext)' -o ) -false \) \
		-exec clang-format -i -verbose {} + 2> /dev/null
	@echo "Done formatting!"

clean:
	rm -f $(OBJ) $(DEP) $(TARGET)

clean_fr: clean
	rm compile_flags.txt
