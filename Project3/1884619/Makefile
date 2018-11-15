# compiler
CC = gcc

# compile flags
CFLAGS = -pthread -Wall -g

# libs
LIBS = -lpthread -lrt -lm

# source files TEST
REDUCER_SRCS = includes/FileParser.c includes/DoublyLinkedList.c includes/Node.c includes/Work.c includes/Multithreader.c includes/Multiprocessor.c includes/Message.c reducer.c
# source files DEPLOYMENT
MAPPER_SRCS = includes/FileParser.c includes/DoublyLinkedList.c includes/Node.c includes/Work.c includes/Multithreader.c includes/Multiprocessor.c includes/Message.c mapper.c

# object files
REDUCER_OBJS = $(REDUCER_SRCS:.c=.o)
MAPPER_OBJS = $(MAPPER_SRCS:.c=.o)

all: reducer mapper

reducer:$(REDUCER_OBJS)
	$(CC) -o reducer $(REDUCER_OBJS) $(LIBS)

mapper:$(MAPPER_OBJS)
	$(CC) -o mapper $(MAPPER_OBJS) $(LIBS)

# generates the object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# cleans stuff
clean:
	rm -f $(REDUCER_OBJS) reducer *~
	rm -f $(MAPPER_OBJS) mapper *~
