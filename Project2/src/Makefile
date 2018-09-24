# compiler
CC = gcc

# compile flags
CFLAGS = -Wall -g

# libs
LIBS = -lm

# source files DEPLOYMENT
SRCS = includes/Process.c includes/FileParser.c includes/DoublyLinkedList.c includes/SchedulingAlgorithms.c sched.c

# object files
OBJS = $(SRCS:.c=.o)

# target DEPLOYMENT
TARG = sched

all: $(TARG)

# generates the target executable
$(TARG):$(OBJS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS)

# generates the object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# cleans stuff
clean:
	rm -f $(OBJS) $(TARG) *~
