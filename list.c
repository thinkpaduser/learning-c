#include <stdio.h>
#include <stdlib.h>

struct list_t {
	int value;
	struct list_t * node;
};

struct list_meta {
	int counter;
	int index;
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

static int cb_printer(int value, void * userdata) { /* Callback printer - just prints each list element's value */
	printf("%d\n", value);
	return 0;
}

static void traverse(struct list_t * list, int (*callback)(int, void *), void * userdata) {
	if (list != NULL) {
		int result = callback(list->value, userdata);
		if (result) {
			return;
		}
		traverse(list->node, callback, userdata);
	}
	return;
}

int main() {
	struct list_t * list = NULL;
	struct list_meta * metadata = NULL; /* Metadata for: 1. Search by index; 2. Count the length */
	list = prepend(list, 10);
	list = prepend(list, 11);
	list = prepend(list, 12);
	list = prepend(list, 13);
	list = remfirst(list);
	traverse(list, cb_printer, NULL);
	return 0;
}
