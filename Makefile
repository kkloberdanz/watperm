CC=cc
OPT=-Os
STD=-std=c89
LDFLAGS=
WARNING=-Werror -Wall -Wextra -Wpedantic -Wfloat-equal -Wundef -Wshadow \
	-Wpointer-arith -Wcast-align -Wstrict-prototypes -Wmissing-prototypes \
	-Wstrict-overflow=5 -Wwrite-strings -Waggregate-return -Wcast-qual \
	-Wswitch-enum -Wunreachable-code -Wformat -Wformat-security -Wvla \

FLAGS=-fstack-protector-all -fPIE -pipe
CFLAGS=$(WARNING) $(STD) $(OPT) $(FLAGS)

watperm: main.c
	$(CC) -o watperm main.c $(CFLAGS) $(LDFLAGS)

.PHONY: release
release: watperm

.PHONY: debug
debug: OPT=-O0 -ggdb3
debug: watperm

.PHONY: static
static: OPT=-Os -static
static: watperm

.PHONY: clean
clean:
	rm -f watperm
