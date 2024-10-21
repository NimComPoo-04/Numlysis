#ifndef _CONTEXT_H_
#define _CONTEXT_H_

typedef struct
{
	void *registrar[52];

	char *data;
	int size;
	int length;
} context_t;

context_t context_create(int initial_size);
void *context_get(context_t *c, char key);
void *context_add(context_t *c, char key, void *data, int size);
void context_destroy(context_t *c);

#endif
