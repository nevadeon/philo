#ifndef FIXED_ARENA_H
# define FIXED_ARENA_H

# include <stddef.h>
# include <stdint.h>
# include <assert.h>
# include <stdbool.h>

typedef struct s_fixed_arena
{
	uint8_t	*mem_start;
	size_t	used_memory;
	size_t	capacity;
}	t_fixed_arena;

void			*fixed_arena_alloc_fn(void *strategy_data, size_t size);
t_fixed_arena	make_fixed_arena(size_t size);
void			free_fixed_arena(t_fixed_arena *arena);
bool			check_fixed_arena(t_fixed_arena *arena);

#endif
