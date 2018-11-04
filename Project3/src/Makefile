# compiler
CC = gcc

# compile flags
CFLAGS = -pthread -Wall -g

# libs
LIBS = -lpthread -lrt -lm

# source files DEPLOYMENT
#SRCS = includes/FileParser.c includes/DoublyLinkedList.c includes/Node.c includes/Multithreader.c includes/Multiprocessor.c mapper.c
# source files TEST
SRCS = includes/FileParser.c includes/DoublyLinkedList.c includes/Node.c includes/Multithreader.c includes/Multiprocessor.c test.c

# object files
OBJS = $(SRCS:.c=.o)

# target DEPLOYMENT
#TARG = mapper
# target TEST
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
