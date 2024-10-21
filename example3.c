#include <stdio.h>
#include <math.h>

#include "integrator.h"

vec_t function(context_t *c)
{
	double x = *(double *)context_get(c, 'X');
	double y = *(double *)context_get(c, 'Y');

	return (vec_t){.x = sin(x) + sin(y), .dim = 1};
}

// Limits for the outer integral
double limit_start_outer(context_t *) { return 0; }
double limit_end_outer  (context_t *) { return 1; }

// Limits for the inner integral
double limit_start_inner(context_t *) { return 0; }

// Using y as a limit for the integral
double limit_end_inner  (context_t *c)
{
	double y = *(double *)context_get(c, 'Y');
	return y;
}

int main(void)
{
	context_t cntx = context_create(sizeof(float));

	integrator_t inner_in = {
		&cntx, 'X', 1, -1, limit_start_inner, limit_end_inner, NULL
	};

	integrator_t outer_in = {
		&cntx, 'Y', 1, -1, limit_start_outer, limit_end_outer, &inner_in
	};

	printf("\nFunction, sin(x) + sin(y)\n");
	printf("Limits Y, %.8lf, %.8lf\n", limit_start_outer(&cntx), limit_end_outer(&cntx));
	printf("Limits X, %.8lf, Y\n", 0.);
	printf("Expected, %.8lf\n\n", 0.45969769);

	printf("Divisions, Variable, H, Start, End, Output\n\n");

	vec_t total = integrator_simpson(&outer_in, function);

	printf("\n,,,, Total, %s\n", vec_str(total));

	context_destroy(&cntx);
}
