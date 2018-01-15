PROG = grpwk
OBJS = template.o linkedlist.o
CC = gcc
CFLAGS = -Wall -O2

.SUFFIXES: .c

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $^
.c.o:
	$(CC) $(CFLAGS) -c $<
clean:
	rm  $(OBJS) $(PROG)
