#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

void *ssbsearch(const void *key, const void *base, size_t nmemb,
		size_t size, int (*compar)(const void *, const void *))
{
	if (!nmemb)
		return NULL;

	register int8_t cmp = compar(key, base + size * (nmemb / 2));
	
	if (cmp > 0)
		return ssbsearch(key, base + size * (nmemb / 2) + size, nmemb / 2, size, compar);
	else if (cmp < 0)
		return ssbsearch(key, base, nmemb / 2, size, compar);
	
	return (void *) base + size * (nmemb / 2);
}
