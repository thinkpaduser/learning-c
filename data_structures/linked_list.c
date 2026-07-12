#include <stdio.h>
#include <stdlib.h>

struct linked_list_t {
	int value;
	struct linked_list_t * node;
};

struct list_meta {
	int counter;
	int index;
};

static struct linked_list_t * prepend(struct linked_list_t * list, int value) {
	struct linked_list_t * next = malloc(sizeof(struct linked_list_t));
	next->value = value;
	next->node = list;
	return next;
}

static struct linked_list_t * remove_first(struct linked_list_t * list) {
	struct linked_list_t * prev = list->node;
	free(list);
	return prev;
}

static int get_index(int value, void * userdata) {
	struct list_meta * metadata = userdata;
	metadata->counter++;
	printf("Value by index %d is: %d\n", metadata->counter, value);
	return 0;
}

static int find_by_index(int value, void * userdata) {
	struct list_meta * metadata = userdata;
	metadata->counter++;
	if (metadata->counter == metadata->index) {
		printf("Found %d by %d index\n", value, metadata->index);
	}
	return 0;
}

static void traverse(struct linked_list_t * list, int (*callback)(int, void *), void * userdata) {
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
	struct linked_list_t * list = NULL;
	struct list_meta metadata;
	list = prepend(list, 10);
	list = prepend(list, 11);
	list = prepend(list, 12);
	list = prepend(list, 13);
	list = remove_first(list);
	metadata.counter = 0;
	metadata.index = 2;
	traverse(list, get_index, &metadata);
	metadata.counter = 0;
	traverse(list, find_by_index, &metadata);
	return 0;
}
