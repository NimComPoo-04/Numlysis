#include  <stdio.h>
#include  <math.h>
#include "integrator.h"

#define PI 3.14159

/*
 * Function here: sin(x)
 * Limits: 0 to PI
 */

vec_t function(context_t *c)
{
	double x = *(double *)context_get(c, 'X');

	return (vec_t){.x = sin(x), .dim = 1};
}

double limit_start(context_t *) { return 0; }
double limit_end(context_t *)   { return PI; }

int main(void)
{
	context_t cntx = context_create(sizeof(float));

	integrator_t in = {
		&cntx, 'X', 1, 1000, limit_start, limit_end, NULL
	};

	printf("\nFunction, sin(x)\n");
	printf("Limits, %.8lf, %.8lf\n", limit_start(&cntx), limit_end(&cntx));
	printf("Expected, %.8lf\n\n", 2.0);

	printf("Divisions, Step, Variable, H, x1, y1, x2, y2, x3, y3, Start, End, Output\n\n");

	vec_t total = integrator_simpson(&in, function);

	printf("\n,,,,,,,,,,, Total, %s\n", vec_str(total));

	context_destroy(&cntx);
}
