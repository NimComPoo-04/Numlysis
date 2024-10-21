#include  <stdio.h>
#include  <math.h>
#include "integrator.h"

#define PI 3.14159

vec_t function(context_t *c)
{
	double x = *(double *)context_get(c, 'X');

	return (vec_t){.x = 1. / sqrt(1 - x * x), .dim = 1};
}

double limit_start(context_t *) { return 0; }
double limit_end(context_t *)   { return 1; }

int main(void)
{
	context_t cntx = context_create(sizeof(float));

	integrator_t in = {
		&cntx, 'X', -1, 50000, limit_start, limit_end, NULL
	};

	printf("\nFunction, 1 / sqrt(1 - x * x)\n");
	printf("Limits, %.8lf, %.8lf\n", limit_start(&cntx), limit_end(&cntx));
	printf("Expected, %.8lf\n\n", 1.570796);

	printf("Divisions, Variable, H, Start, End, Output\n\n");

	vec_t total = integrator_simpson(&in, function);

	printf("\n,,,,,, Total, %s\n", vec_str(total));

	context_destroy(&cntx);
}
