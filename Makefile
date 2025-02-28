CC=gcc
CFLAGS=-Wall -DTOTO -I.
OBJS=main.o
EXE=tp6.exe

help:
	@echo "taper make all"

all: $(OBJS) rtest
	@echo "### Gen exe"
	gcc $(OBJS) -o $(EXE)
	@echo "### fini"

rtest:
	@echo "### Je lance le test"

clean:
	rm -f $(OBJS) $(EXE)   