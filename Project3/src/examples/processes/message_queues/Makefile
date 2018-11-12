
# tutorial - http://beej.us/guide/bgipc/html/multi/mq.html

# compiler
CC = gcc

# compile flags
CFLAGS = -Wall -g

# libs
LIBS = -lrt

# source files TEST
SENDER_SRCS = ../../../includes/Node.c ../../../includes/Message.c sender.c
# source files DEPLOYMENT
RECEIVER_SRCS = ../../../includes/Node.c ../../../includes/Message.c receiver.c

# object files
SENDER_OBJS = $(SENDER_SRCS:.c=.o)
RECEIVER_OBJS = $(RECEIVER_SRCS:.c=.o)

all: sender receiver

sender : $(SENDER_OBJS)
	$(CC) -o sender $(SENDER_OBJS) $(LIBS)

receiver: $(RECEIVER_OBJS)
	$(CC) -o receiver $(RECEIVER_OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SENDER_OBJS) sender *~
	rm -f $(RECEIVER_OBJS) receiver *~
