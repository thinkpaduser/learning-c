#include <stdio.h>
#include <stdlib.h>

struct btree_t {
	int value;
	struct btree_t * left;
	struct btree_t * right;
};

struct btree_t * addnode (struct btree_t * tree, int value){
	/* TODO: Add a new node to binary tree */
	return someptr;
}

int main() {
	struct btree_t * tree = NULL;
	tree = addnode(tree, 10);
	return 0;
}
