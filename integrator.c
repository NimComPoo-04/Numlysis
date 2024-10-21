#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "integrator.h"

static vec_t integrator_simpson_internal(integrator_t *in, int N, double start, double end, vec_t(*function)(context_t *c))
{
	context_t *wat = in->context;

	int mult = 1;
	if(end < start)
	{
		double t = start;
		start = end;
		end = t;

		mult = -1;
	}

	double *x = context_get(wat, in->var); assert(x);
	*x = start;

	// Because we will do simpson
	const double h = (end - start) / (2. * N);

	vec_t total = {0};

	int step = 1;
	vec_t y1, y2, y3;


	if(start != end)
	{
		while(*x <= end)
		{
			if(!in->next)
			{
				y1 = function(wat);  *x += h;
				y2 = function(wat);  *x += h;
				y3 = function(wat);
			}
			else
			{

				y1 = integrator_simpson(in->next, function);   *x += h;
				y2 = integrator_simpson(in->next, function);   *x += h;
				y3 = integrator_simpson(in->next, function);
			}

			total = vec_add(vec_scl(vec_add(vec_add(y1, vec_scl(y2, 4)), y3), mult * h / 3), total);

			if(in->smpl > 0 && in->iter > 0)
			{
				// If we want to see something specifing show something specific
				printf("%d, %d, %c, %.8lf, ", N, step++, in->var, h);

				printf("%.8lf, %s, ", *x - 2 * h, vec_str(y1));
				printf("%.8lf, %s, ", *x - 1 * h, vec_str(y2));
				printf("%.8lf, %s, ", *x - 0 * h, vec_str(y3));

				printf("%.8lf, %.8lf, %s\n", mult == -1 ? end : start, mult == -1 ? start : end, vec_str(total));
			}
		}
		if(in->smpl <= 0 || in->iter <= 0)
		{
			// if we do not want to see something specific, just don't
			printf("%d, %c, %.8lf, ", N, in->var, h);
			printf("%.8lf, %.8lf, %s\n", mult == -1 ? end : start, mult == -1 ? start : end, vec_str(total));
		}
	}

	return total;
}

vec_t integrator_simpson(integrator_t *in, vec_t(*function)(context_t *c))
{
	vec_t total = {0};

	double *x = context_get(in->context, in->var);
	if(!x) x = context_add(in->context, in->var, NULL, sizeof(double));

	double start = in->start(in->context);
	double end   = in->end(in->context);
	
	float f1 = 0, f2 = 0;

	if(!in->next)
	{
		*x = start; f1 = vec_len(function(in->context));
		*x = end;   f2 = vec_len(function(in->context));
	}

	// Movement for start and end
	double Dstart = (start >= 1E6 || start <= -1E6) ? fabs(start) - 100 : 0;
	double Dend   = (end >= 1E6 || end <= -1E6) ? fabs(end) - 100 : 0;

	// Oviously if we computing using infinity we need to address that first
	if(Dstart == 0) Dstart = (fabs(f1) >= 1E6 || isnan(f1)) ? fabs(start) / 10. : 0;
	if(Dend == 0) Dend = (fabs(f2) >= 1E6 || isnan(f2)) ? fabs(end) / 10. : 0;

	float h = (end - Dend - start - Dstart) / in->smpl;	

	for(int iter = 0; iter != (in->iter == 0 ? 1 : in->iter); iter++)
	{
		double N = in->smpl <= 0 ? 1 : (end - Dend - start - Dstart) / h;
		double CAP = in->smpl <= 0 ? 1E6 : (end - Dend - start - Dstart) / h;

		double len = 0;
		
		vec_t old_total = total;

		while(N <= CAP)
		{
			vec_t new_total = integrator_simpson_internal(in, (int)round(N), start + Dstart, end - Dend, function); N += 1;

			len = vec_len(vec_sub(new_total, total));

			// We get out if we go somewhere strange
			if(fabs(len) < 1E-10 || len > 1E10 || len < -1E10) break;

			total = new_total;
		}

		len = vec_len(vec_sub(old_total, total));
		if(fabs(len) < 1E-10 || len > 1E10 || len < -1E10 || isnan(len))
		{
			total = old_total;
			break;
		}

		Dstart *= 0.99;
		Dend   *= 0.99;
	}

	return total;
}
