//single linked list
#include "xmalloc.c"
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	void *data;
	struct node *next;
} node;

typedef struct list {
	node *front;
	node *end;
} list;

void list_start(list *l)
{
	if (!l)
		return;
	l->front = l->end = NULL;
}

node *new_node(void *elem)
{
	node *ret = xmalloc(sizeof(node));
	ret->data = elem;
	ret->next = NULL;
	return ret;
}

void list_push_back(list *l, void *data)
{
	if (!l->end) {
		l->front = l->end = new_node(data);
		return;
	}

	l->end->next = new_node(data);
}

void list_push_front(list *l, void *data)
{
	if (!l->front) {
		l->front = l->end = new_node(data);
		return;
	}

	node *add = new_node(data);
	add->next = l->front;
	l->front = add;
}

void list_pop_front(list *l)
{
	if (!l->front)
		return;
	node *tmp = l->front->next;
	free(l->front);
	l->front = tmp;
}

void node_clear(node *n)
{
	if (n->next)
		node_clear(n->next);
	free(n);
}

void list_clear(list *l)
{
	node_clear(l->front);
}
