SRCFILES := src/main.c src/circ.c src/send.c
INCLUDES := -I include/

CC := clang

override CCFLAGS += -std=c11 -pedantic-errors -fdiagnostics-show-option \
					-Werror -Weverything \
					-Wno-padded #\
#					-Wno-cast-qual -Wno-missing-prototypes -Wno-vla

EXECUTABLE ?= libcirc-example

all: ${EXECUTABLE}

${EXECUTABLE}:
	$(CC) $(CCFLAGS) $(INCLUDES) ${SRCFILES} -o $@

clean:
	@find -name '*.o' -delete
	@rm -f ${EXECUTABLE}

.PHONY: all clean
