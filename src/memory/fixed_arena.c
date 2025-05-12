#include <stdlib.h>
#include <assert.h>
#include "fixed_arena.h"

void	init_fixed_arena_data(t_fixed_arena_data *arena, size_t size)
{
	arena->mem_start = malloc(size);
	assert(arena->mem_start);
	arena->used_memory = 0;
	arena->capacity = size;
}

void	free_fixed_arena_data(t_fixed_arena_data *arena)
{
	free(arena->mem_start);
	arena->mem_start = NULL;
	arena->used_memory = 0;
	arena->capacity = 0;
}

void	*fixed_arena_alloc_fn(void *strategy_data, size_t size)
{
	t_fixed_arena_data	*arena;
	void				*ptr;

	arena = (t_fixed_arena_data *)strategy_data;
	if (arena->used_memory + size > arena->capacity)
		return (NULL);
	ptr = arena->mem_start + arena->used_memory;
	arena->used_memory += size;
	return (ptr);
}
