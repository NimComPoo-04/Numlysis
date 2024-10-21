#include <stdio.h>
#include <math.h>

#include "vector.h"

#define VEC_OP(N, T) vec_t vec_##N(vec_t a, vec_t b)\
{\
	a.dim = a.dim > b.dim ? a.dim : b.dim;\
	for(int i = 0; i < a.dim; i++)\
		a.it[i] = a.it[i] T b.it[i];\
	return  a;\
}

VEC_OP(add, +);
VEC_OP(sub, -);
VEC_OP(mul, *);
VEC_OP(div, /);

double vec_len(vec_t a)
{
	double length = 0;
	for(int i = 0; i < a.dim; i++)
		length += a.it[i] * a.it[i];

	return sqrt(length);
}

vec_t vec_scl(vec_t a, double b)
{
	for(int i = 0; i < a.dim; i++)
		a.it[i] *= b;

	return a;
}

char *vec_str(vec_t a)
{
	static char str[256];

	int pos = sprintf(str, "(");
	if(a.dim == 0)
		sprintf(str + pos, ")");

	for(int i = 0; i < a.dim; i++)
	{
		pos += sprintf(str + pos, "%.8lf", a.it[i]);

		if(i == a.dim - 1)
			pos += sprintf(str + pos, ")");
		else
			pos += sprintf(str + pos, ", ");
	}

	return str;
}
