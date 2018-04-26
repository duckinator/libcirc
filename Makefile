SRCFILES := src/main.c
INCLUDES := -I include/

CC := clang

override CCFLAGS += -std=c11 -Wall -g -Wextra -Wunused -Wformat=2 -Winit-self -Wmissing-include-dirs -Wstrict-overflow=4 -Wwrite-strings -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas -Wcast-align -Wmissing-noreturn -Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code -Winline -Winvalid-pch -Wdisabled-optimization -Wbad-function-cast -Wunused-function -Werror=implicit-function-declaration -Wno-suggest-attribute=format -gdwarf-2 -pedantic-errors -O0

EXECUTABLE ?= libcirc-example

all: ${EXECUTABLE}

${EXECUTABLE}:
	$(CC) $(CCFLAGS) $(INCLUDES) ${SRCFILES} -o $@

clean:
	@find -name '*.o' -delete
	@rm -f ${EXECUTABLE}

.PHONY: all clean
