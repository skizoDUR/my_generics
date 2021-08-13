/*
  sortgeneric.c -- Quicksort generic for C
*/

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#define GNUSWAP(a, b, size)			\
	size_t l_size = size;			\
	char *x = (char *)(a);			\
	char *y = (char *)(b);			\
	while (l_size--) {			\
		char tmp = *x;			\
		*x = *y;			\
		*y = tmp;			\
		x++;				\
		y++;				\
	}					\


size_t qpart(void *base, size_t size, int32_t l, int32_t r, int (*compar)(const void *, const void *))
{
	char p[size];
	memcpy(p, base + (size * ((l + r) / 2)), size);
	l--;
	r++;
	
	while (l < r) {
		do { l++; } while (compar(base + (size * l), &p) < 0);
		do { r--; } while (compar(base + (size * r), &p) > 0);

		if (l < r) {
			void *l_tmp = base + (size * l);
			void *r_tmp = base + (size * r);
			GNUSWAP(l_tmp, r_tmp, size);
		}
		
	}
	return r;
}

void q_call(void *base, size_t size, int l, int r, int (*compar)(const void *, const void *))
{
	if (l >= r)
		return;
	int p = qpart(base, size, l, r, compar);
	q_call(base, size, l, p, compar);
	q_call(base, size, p + 1, r, compar);
}

void ssqsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
	q_call(base, size, 0, nmemb - 1, compar);
}


/*original CAR quicksort

size_t intpart(int *ar, int l, int r)
{
	int p = ar[(l + r) / 2];
	l--;
	r++;
	
	while (l < r) {
			
//		while (ar[++l] < p);
//		while (ar[--r] > p);
		do {
			l++;
				
		} while (ar[l] < p);
		
		do {
			r--;
			
		} while (ar[r] > p);

		
		if (l < r) {
			int tmp = ar[r];
			ar[r] = ar[l];
			ar[l] = tmp;
		}
	}

	return r;
}

void intsort(int *ar, int l, int r)
{
	if (l >= r)
		return;
	size_t p = intpart(ar, l, r);
	intsort(ar, l, p);
	intsort(ar, p + 1, r);
}
*/
