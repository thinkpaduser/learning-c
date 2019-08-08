#include <stdio.h>
#include <stdlib.h>

struct btree_t {
	int value;
	struct btree_t * left;
	struct btree_t * right;
};

struct btree_t * addnode (struct btree_t * tree, int value){
	/* TODO: Add a new node to binary tree */
	if (tree == NULL) {
		tree = malloc(sizeof(struct btree_t));
		tree->value = value;
	}
	return tree;
}

int main() {
	struct btree_t * tree = NULL;
	tree = addnode(tree, 10);
	printf("%d\n", tree->value);
	return 0;
}
