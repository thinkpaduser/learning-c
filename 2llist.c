#include <stdio.h>
#include <stdlib.h>

typedef struct dlist_t {
	int value;
	struct dlist_t * next;
	struct dlist_t * prev;
} dlist_t;

dlist_t * prepend(struct dlist_t * list, int value) {  /* Also used as init() proc */
	if (list != NULL) {
		dlist_t * next = malloc(sizeof(dlist_t));
		next->value = value;
		list->next = next;
	}
	list = malloc(sizeof(dlist_t));                /* Initialize root element here */
	list->value = value;
	list->next = NULL;
	list->prev = NULL;
	return list;
}

void print_root(dlist_t * list) {
	if (list == NULL) {
		printf("Empty list\n");
	}
	printf("%d\n", list->value);
}

dlist_t * next(dlist_t * list) {
	if (list->next == NULL) {
		printf("Next element does not exist\n");
		return NULL;
	}
	return list->next;
}

dlist_t * prev(dlist_t * list) {
	if (list->prev == NULL) {
		printf("Previous element does not exist\n");
		return NULL;
	}
	return list->prev;
}

dlist_t * rm_first(dlist_t * list){
	/* TODO relink; free(first) */
	return list;
}

int main(void) {
	dlist_t * new_list; /* == NULL */
	new_list = prepend(new_list, 228);
	print_root(new_list);
	return 0;
}
