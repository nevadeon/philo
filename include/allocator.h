#ifndef ALLOCATOR_H
# define ALLOCATOR_H

# include <stddef.h>
# include <assert.h>

typedef void	*(*t_alloc_fn)(void *strategy_data, size_t size);

typedef struct s_allocator
{
	void		*strategy_data;
	t_alloc_fn	strategy_fn;
}	t_allocator;

void		*mem_alloc(t_allocator *allocator, size_t size);
t_allocator	make_allocator(void *data, t_alloc_fn function);

#endif
