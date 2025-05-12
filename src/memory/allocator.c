#include "allocator.h"

void	*mem_alloc(t_allocator *allocator, size_t size)
{
	if (!allocator || !allocator->strategy_fn)
		return (NULL);
	return (allocator->strategy_fn(allocator->strategy_data, size));
}

void	init_allocator(t_allocator *alloc, void *data, t_alloc_fn function)
{
	alloc->strategy_data = data;
	alloc->strategy_fn = function;
}
