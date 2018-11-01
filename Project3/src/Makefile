# compiler
CC = gcc

# compile flags
CFLAGS = -pthread -Wall -g

# libs
LIBS = -lpthread -lrt

# source files DEPLOYMENT
SRCS = includes/FileParser.c includes/DoublyLinkedList.c includes/Node.c includes/Multiprocessor.c

# object files
OBJS = $(SRCS:.c=.o)

all: mapper reducer

mapper: mapper.o
	$(CC) -o mapper mapper.o $(OBJS) $(LIBS)

reducer: reducer.o
	$(CC) -o reducer reducer.o $(OBJS) $(LIBS)

# generates the object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# cleans stuff
clean:
	rm -f $(OBJS) $(TARG) *~
