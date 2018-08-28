# compiler
CC = gcc

# compile flags
CFLAGS = -Wall -g

# libs
LIBS = -lm

# source files
SRCS = includes/DoublyLinkedList.c includes/Node.c includes/FileParser.c tests/FileParserTest.c tests/NodeTest.c tests/DoublyLinkedListTest.c test.c

# object files
OBJS = $(SRCS:.c=.o)

TARG = test

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