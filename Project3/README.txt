Project completed by: Jacob Taylor Cassady (1884619)

As far as I am aware, the project meets the requirements as described completely.

My message struct is copied below.  I chose this size for the message because no word
will exceed MAXWORDSIZE in length and words are what we are sending via message.  Also,
I decided to send each word count number of times to reduce the complexity of the message
struct.

typedef struct message_struct {
  long mtype;
  char word[MAXWORDSIZE];
} Message;
