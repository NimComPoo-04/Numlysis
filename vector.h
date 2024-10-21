#ifndef _VECTOR_H_
#define _VECTOR_H_

#define MAX_DIMENTION 4

typedef struct
{
	union
	{
		double it[MAX_DIMENTION];
		struct{double x, y, z, w;};
	};
	int dim;
} vec_t;

vec_t vec_add(vec_t a, vec_t b);
vec_t vec_sub(vec_t a, vec_t b);
vec_t vec_mul(vec_t a, vec_t b);
vec_t vec_div(vec_t a, vec_t b);

double vec_len(vec_t a);
vec_t vec_scl(vec_t a, double b);

char *vec_str(vec_t a);

#endif
