#ifndef NODE
#define NODE

typedef struct NodeT {
	char *word;
	int count;
	struct NodeT *nextNode;
	struct NodeT *previousNode;
} Node;

Node* create_node(char *);

void print_node(Node *);

void copy_node(Node *, Node *);

int compare_node_by_word(Node *node1, Node *node2);

void delete_node(Node *);

#endif