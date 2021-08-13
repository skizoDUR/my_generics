/*
  queue.c -- 
*/
#include "xmalloc.c"
#include <stdio.h>
#include <stdlib.h>

typedef struct queue_node {
	void *next;
	void *elem;
} queue_node;

typedef struct queue {
	queue_node *front;
	queue_node *rear;
	size_t size;
} queue;

void queue_init(queue *q)
{
	q->front = q->rear = NULL;
	q->size = 0;
}

void enqueue(queue *q, void *item)
{
	if (!q->front || !q->rear) {
		q->rear = q->front = xmalloc(sizeof(queue_node));
		q->front->next = NULL;
		q->front->elem = item;
		q->size++;
		return;
	}

	queue_node *add = xmalloc(sizeof(queue_node));
	add->next = q->rear;
	add->elem = item;
	q->rear = add;
	q->size++;
}

void dequeue(queue *q)
{
	if (!q->front || !q->rear)
		return;
	queue_node *seek = NULL;
	for (seek = q->rear; seek->next != q->front && seek->next; seek = seek->next);
	free(q->front);
	q->front = seek;
	q->front->next = NULL;
	q->size--;
	if (!q->size)
		q->front = q->rear = NULL;
}

void dq_all(queue_node *qn)
{
	if (!qn)
		return;
	dq_all(qn->next);
	free(qn);
}

void dequeue_all(queue *q)
{
	dq_all(q->rear);
	q->front = q->rear = NULL;
	q->size = 0;
}		
