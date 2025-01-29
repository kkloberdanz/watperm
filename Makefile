CC=cc
OPT=-O2
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

.PHONY: clean
clean:
	rm -f watperm
