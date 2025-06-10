#include "philo.h"

static size_t	_compute_required_memory(char const *argv[])
{
	int		nb_philos;
	size_t	total;

	nb_philos = atou(argv[NB_OF_PHILO_INDEX]);
	if (nb_philos > 200)
		exit_error(ERR_TOO_MANY_PHILO);
	total = nb_philos * (\
		2 * sizeof(pthread_t) \
		+ sizeof(pthread_mutex_t) \
		+ sizeof(t_thread_arg) \
	);
	return (total);
}

int	main(int argc, char const *argv[])
{
	t_data	data;
	t_alloc	*arena_alloc;

	if (argc < 5 || argc > 6)
		exit_error(ERR_USAGE);
	arena_alloc = new_block_allocator(_compute_required_memory(argv));
	if (!arena_alloc)
		exit_error(ERR_FAILED_ALLOCATION);
	data = make_data(arena_alloc, argc, argv);
	init_mutexes(&data);
	init_threads(&data);
	wait_threads(&data);
	destroy_mutexes(&data);
	free_allocator(&arena_alloc);
	return (0);
}
