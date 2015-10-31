#include <stdio.h>
#include <stdlib.h>

#define NA -1


typedef struct Node
{
	int val;
	struct Node* left;
	struct Node* right;	
} Node;


Node new_node(int val, Node* left, Node* right)
{
	return (Node) {.val = val, .left = left, .right = right};
}


/*
 * Constructs decision tree
 */
Node* construct_decision_tree(int* bits, int size) 
{	
	Node* leaf = malloc(size * sizeof(Node));

	for (int i = 0; i < size; i++) {
		leaf[i] = new_node(bits[i], NULL, NULL);
	}

	size >>= 1;

	Node* tmp;


	while (size > 0) {
		tmp = malloc(size * sizeof(Node));

		for (int i = 0; i < size; i++) {
			tmp[i] = new_node(NA, &leaf[i << 1], &leaf[(i << 1) + 1]);
		}

		size >>= 1;
		leaf = tmp;
	}
	
	return &tmp[0];
}


int wander(Node* root, int* bits, int size)
{
	Node* tmp = root;

	for (int i = 0; i < size; i++) {
		if (bits[i]) {
			tmp = tmp->right;
		} else {
			tmp = tmp->left;
		}
	}
	return tmp->val;
}


/*
 * Frees root and its subtree.
 */
void free_tree(Node *root) 
{
	if (root->val == NA) {
		free(root);
	} else {
		free_tree(root->left);
		free_tree(root->right);
	}
}


int main(void)
{

	/*
	 *			┌───┐	
	 *			│x_1│
	 *			└───┘
	 *   			╱   ╲
	 * 		       ╱     ╲
	 *		      ╱	      ╲	
	 *		     ╱	       ╲
	 *		   0╱		╲1
	 *		   ╱		 ╲
	 *		  ╱		  ╲	
	 *		 ╱		   ╲
	 *		╱		    ╲
	 *	    ┌───┐	 	    ┌───┐
	 *	    │x_2│ 		    │x_2│
	 *	    └───┘ 		    └───┘
	 *   	    ╱ 	╲		    ╱   ╲
	 *        0╱     ╲1               0╱     ╲1 
	 *        ╱       ╲               ╱       ╲  
	 *    ┌───┐	  ┌───┐       ┌───┐	  ┌───┐
	 *    │x_3│	  │x_3│       │x_3│       │x_3│
	 *    └───┘	  └───┘       └───┘       └───┘
	 *   0╱   ╲1	 0╱   ╲1     0╱   ╲1	 0╱   ╲1
	 *   ╱     ╲	 ╱     ╲     ╱     ╲     ╱     ╲	
	 * ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐
	 * │ 0 │ │ 0 │ │ 1 │ │ 1 │ │ 1 │ │ 0 │ │ 1 │ │ 0 │
	 * └───┘ └───┘ └───┘ └───┘ └───┘ └───┘ └───┘ └───┘	
	 */


	int bits[] = {0, 0, 1, 1, 1, 0, 1, 0};
	
	Node* root = construct_decision_tree(bits, sizeof(bits)/sizeof(int));
	
	
	int path[] = 
		{ 	1, // x_1
	 		1, // x_2
	 		1  // x_3  
	 	};

	printf("%d\n", wander(root, path, 3) );

	free_tree(root);

	return 0;
}