#include <stdio.h>
#include <stdlib.h>

struct list_t {
	int value;
	struct list_t * node;
};

static struct list_t * prepend(struct list_t * list, int value) {
	struct list_t * next = malloc(sizeof(struct list_t));
	next->value = value;
	next->node = list;
	return next;
}

static struct list_t * remfirst(struct list_t * list) {
	struct list_t * prev = list->node;
	free(list);
	return prev;
}

int main() {
	struct list_t * list = NULL;
	list = prepend(list, 10);
	list = prepend(list, 11);
	list = remfirst(list);
	printf("%d\n", list->value);
	return 0;
}
