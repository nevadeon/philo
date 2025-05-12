#include <stdlib.h>
#include <assert.h>
#include "fixed_arena.h"

t_fixed_arena	make_fixed_arena(size_t size)
{
	t_fixed_arena	arena;

	arena = (t_fixed_arena){
		.mem_start = malloc(size),
		.used_memory = 0,
		.capacity = size,
	};
	assert(arena.mem_start);
	return (arena);
}

void	free_fixed_arena(t_fixed_arena *arena)
{
	free(arena->mem_start);
	arena->mem_start = NULL;
	arena->used_memory = 0;
	arena->capacity = 0;
}

void	*fixed_arena_alloc_fn(void *strategy_data, size_t size)
{
	t_fixed_arena	*arena;
	void			*ptr;

	arena = (t_fixed_arena *)strategy_data;
	if (arena->used_memory + size > arena->capacity)
		return (NULL);
	ptr = arena->mem_start + arena->used_memory;
	arena->used_memory += size;
	return (ptr);
}
