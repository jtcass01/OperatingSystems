# compiler
CC = gcc

# compile flags
CFLAGS = -pthread -Wall -g

# libs
LIBS = -lpthread -lrt

# source files DEPLOYMENT
SRCS = includes/DoublyLinkedList.c includes/Node.c mapper.c reducer.c

# object files
OBJS = $(SRCS:.c=.o)

TARG = mapper reducer

all: $(TARG)

mapper: mapper.o
	$(CC) -o mapper mapper.o $(LIBS)

reducer: reducer.o
	$(CC) -o reducer reducer.o $(LIBS)

# generates the object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# cleans stuff
clean:
	rm -f $(OBJS) $(TARG) *~
