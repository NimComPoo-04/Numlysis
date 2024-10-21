#include <stdlib.h>
#include <string.h>
#include "context.h"

context_t context_create(int initial_size)
{
	context_t c = {0};
	c.size = initial_size;
	c.data = calloc(initial_size, 1);
	return c;
}

void *context_get(context_t *c, char key)
{
	if(key >= 'A' && key <= 'Z')
		return c->registrar[key - 'A'];
	else if(key >= 'a' && key <= 'z')
		return c->registrar[key - 'a' + 26];
	else
		return NULL;
}

void *context_add(context_t *c, char v, void *data, int size)
{
	int key = 0;
	if(v >= 'A' && v <= 'Z') key = v - 'A';
	else if(v >= 'a' && v <= 'z')  key = v - 'a' + 26;
	else return 0;

	if(c->registrar[key])
		return NULL;

	c->registrar[key] = c->data + c->length;

	if(c->length + size > c->size)
	{
		c->size += c->length + size + 256;
		c->data = realloc(c->data, c->size);
	}

	if(data != NULL)
		memcpy(c->data + c->length, data, size);
	c->length += size;

	return c->registrar[key];
}

void context_destroy(context_t *c)
{
	free(c->data);
}
