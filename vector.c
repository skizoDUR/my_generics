/*
  vector.c -- 
*/
#include "xmalloc.c"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct vector {
	void *elem;
	void *last;
	size_t size;
	size_t nmemb;
	size_t avail_space;
	
}vector;

void vector_push_back(void *elem, vector *v)
{
	if (v->nmemb * v->size >= v->avail_space) {
		v->avail_space *= 2;
		v->elem = realloc(v->elem, v->avail_space);
		v->last = v->elem + (v->nmemb - 1) * v->size;
	}
	uint8_t *write = NULL;
	if (v->last)
		write = v->last + v->size;
	else
		write = v->elem;
	memcpy(write, elem, v->size);
	v->last = write;
	v->nmemb++;
}

void *vector_index(size_t i, vector *v)
{
	return v->elem + v->size * i;
}

void vector_free(vector *v)
{
	free(v->elem);
}

void vector_start(vector *v, size_t nmemb, size_t size)
{
	v->elem = xmalloc(size * nmemb);
	v->last = NULL;
	v->nmemb = 0;
	v->avail_space = size * nmemb;
	v->size = size;
}

size_t vector_size(vector *v)
{
	return v->nmemb;
}
