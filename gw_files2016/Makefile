PROG = grpwk
OBJS = template.o
CC = gcc
CFLAGS = -Wall

.SUFFIXES: .c

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $^
.c.o:
	$(CC) $(CFLAGS) -c $<
clean:
	rm  $(OBJS) $(PROG)
