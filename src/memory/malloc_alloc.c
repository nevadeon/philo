#include <stdlib.h>
#include "allocator.h"

static void	*_malloc_alloc_fn(void *strategy_data, size_t size)
{
	(void)strategy_data;
	return (malloc(size));
}

const t_allocator	*malloc_alloc(void)
{
	static const t_allocator	malloc_alloc = {
		.strategy_data = NULL,
		.strategy_fn = _malloc_alloc_fn
	};

	return (&malloc_alloc);
}
