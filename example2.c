#include <stdio.h>
#include <math.h>

#include "integrator.h"

vec_t function(context_t *c)
{
	double x = *(double *)context_get(c, 'X');

	return (vec_t){.x = exp(0.05 * -x * x), .dim = 1};
}

// In the event that the limits cross 1E6 we trigger the improper integral,
// this will make the program print less data and focus more on getting results

double limit_start(context_t *) { return -1E7; }
double limit_end(context_t *)   { return 1E7; }


int main(void)
{
	context_t cntx = context_create(sizeof(float));

	integrator_t in = {
		&cntx, 'X', -1, 50, limit_start, limit_end, NULL
	};

	printf("\nFunction, exp(0.05 * -x * x)\n");
	printf("Limits, %.8lf, %.8lf\n", limit_start(&cntx), limit_end(&cntx));
	printf("Expected, %.8lf\n\n", 7.9266);

	printf("Divisions, Variable, H, Start, End, Output\n\n");

	vec_t total = integrator_simpson(&in, function);

	printf("\n,,,, Total, %s\n", vec_str(total));

	context_destroy(&cntx);
}
