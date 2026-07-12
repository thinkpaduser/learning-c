#include <stdlib.h>
#include <stdio.h>

struct bintree_t {
	int value;
	struct bintree_t * left;
	struct bintree_t * right;
};

struct bintree_t * add_node (struct bintree_t * tree, int value){
	if (tree == NULL) {
		tree = malloc(sizeof(struct bintree_t));
		tree->value = value;
		return tree;
	}
	struct bintree_t * node = malloc(sizeof(struct bintree_t));
	if (tree->value <= value) {
		if (tree->right != NULL) {
			add_node(tree->right, value);
		} else {
			tree->right = node;
		}
	} else if (tree->value > value) {
		if (tree->left != NULL) {
			add_node(tree->left, value);
		} else {
			tree->left = node;
		}
	}
	node->value = value;
	return tree;
}

int main(){
	struct bintree_t * tree = NULL;
	tree = add_node(tree, 228);
	tree = add_node(tree, 1337);
	tree = add_node(tree, 1488);
	tree = add_node(tree, 123);
	tree = add_node(tree, 122);
	tree = add_node(tree, 14);
	printf("%d\t%d\t%d\t%d\t%d\n", tree->value, tree->right->value, tree->right->right->value, tree->left->value, tree->left->left->value);
	return 0;
}
