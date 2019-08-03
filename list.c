#include <stdio.h>
#include <stdlib.h>

struct list_t {
	int value;
	struct list_t * node;
};

struct list_t * prepend(struct list_t * list, int value) {
	struct list_t * next = malloc(sizeof(struct list_t));
	next->value = value;
	next->node = list;
	return next;
}

int main() {
	struct list_t * list = NULL;
	list = prepend(list, 10);
	printf("%d\n", list->value);
	return 0;
}
