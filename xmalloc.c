#include <stdlib.h>
#include <stdio.h>
void *xmalloc(size_t size)
{
	void *ret = malloc(size);
	if (!ret) {
		fprintf(stderr, "malloc failed to allocate\n");
		abort();
	}
	return ret;
}
