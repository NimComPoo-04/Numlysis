#include <stdio.h>
#include <math.h>

#include "integrator.h"

vec_t function(context_t *c)
{
	return (vec_t){.x = 1, .dim = 1};
}

// Limits for the outer integral
double limit_start_outer(context_t *) { return -1; }
double limit_end_outer  (context_t *) { return 1; }

// Limits for the inner integral
double limit_start_inner(context_t *c)
{
	double y = *(double *)context_get(c, 'Y');
	return -sqrt(1 - y * y);
}

// Using y as a limit for the integral
double limit_end_inner  (context_t *c)
{
	double y = *(double *)context_get(c, 'Y');
	return sqrt(1 - y * y);
}

int main(void)
{
	context_t cntx = context_create(sizeof(float));

	integrator_t inner_in = {
		&cntx, 'X', 1, -1, limit_start_inner, limit_end_inner, NULL
	};

	integrator_t outer_in = {
		&cntx, 'Y', 0, 4000, limit_start_outer, limit_end_outer, &inner_in
	};

	printf("\nFunction, 1\n");
	printf("Limits Y, %.8lf, %.8lf\n", -1., 1.);
	printf("Limits X, -sqrt(1 - y * y), sqrt(1 - y * y)\n");
	printf("Expected, %.8lf\n\n", 3.14159);

	printf("Divisions, Variable, H, Start, End, Output\n\n");

	vec_t total = integrator_simpson(&outer_in, function);

	printf("\n,,,, Total, %s\n", vec_str(total));

	context_destroy(&cntx);
}
