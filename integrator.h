#ifndef _INTEGRATOR_H_
#define _INTEGRATOR_H_

#include "context.h"
#include "vector.h"

#define MAX_ITERATION 1E6

typedef struct integrator_t
{
	context_t *context;		// generate a context for variables

	char var;			// variable of operations
	int  iter;			// number of iterations to perform (0) is till convergence or divergence
	int  smpl;			// number of samples from the function to take

	double (*start)(context_t *);	// limits
	double (*end)(context_t *);

	struct integrator_t *next;
} integrator_t;

vec_t integrator_simpson(integrator_t *wat, vec_t(*function)(context_t *));

#endif
