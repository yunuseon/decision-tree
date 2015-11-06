typedef struct Node
{
	int val;
	struct Node* left;
	struct Node* right;	
} Node;

Node new_node(int val, Node* left, Node* right);
Node* construct_decision_tree(int* bits, int size);

int wander(Node* root, int* bits, int size);

void free_tree(Node *root);

