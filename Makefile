CC = gcc
LIB = -lpthread
EXE0 = part22.exe
EXE1 = part1.exe
EXE2 = part1.1.exe
#EXE3 = pthreads_pi.exe

%.exe : %.o
	$(CC) $(LIB) -o $@ $^

%.o : %.c
	$(CC) $(LIB) -c -o $@ $^

all: $(EXE0) $(EXE1) $(EXE2) $(EXE3)

clean:
	rm -f *.exe *.o
