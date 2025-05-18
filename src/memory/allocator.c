#include "allocator.h"

void	*mem_alloc(t_allocator *allocator, size_t size)
{
	assert(allocator);
	assert(allocator->alloc_fn);
	return (allocator->alloc_fn(allocator->data, size));
}

bool	check_allocator_data(t_allocator *allocator)
{
	assert(allocator);
	assert(allocator->check_fn);
	return (allocator->check_fn(allocator->data));
}

void	free_allocator_data(t_allocator *allocator)
{
	assert(allocator);
	assert(allocator->free_fn);
	allocator->free_fn(allocator->data);
}
