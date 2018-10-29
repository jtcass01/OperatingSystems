# compiler
CC = gcc

# compile flags
CFLAGS = -pthread -Wall -g

# libs
LIBS = -lpthread -lrt

# source files DEPLOYMENT
SRCS = includes/FileParser.c includes/DoublyLinkedList.c includes/Node.c mapper.c reducer.c

# object files
OBJS = $(SRCS:.c=.o)

TARG = mapper

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
