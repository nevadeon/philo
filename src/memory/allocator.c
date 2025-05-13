#include "allocator.h"

void	*mem_alloc(t_allocator *allocator, size_t size)
{
	assert(allocator);
	assert(allocator->strategy_fn);
	return (allocator->strategy_fn(allocator->strategy_data, size));
}

t_allocator	make_allocator(void *data, t_alloc_fn function)
{
	t_allocator	allocator;

	assert(function);
	allocator = (t_allocator){
		.strategy_data = data,
		.strategy_fn = function,
	};
	return (allocator);
}
