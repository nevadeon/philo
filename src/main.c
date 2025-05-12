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
	t_data				data;
	t_allocator			alloc_arena;
	t_fixed_arena_data	arena_data;

	if (argc < 5 || argc > 6)
		exit_error(ERR_USAGE);
	arena_data = make_fixed_arena_data(_compute_required_memory(argv));
	alloc_arena = make_allocator(&arena_data, fixed_arena_alloc_fn);
	data = make_data(&alloc_arena, argc, argv);
	init_mutexes(&data);
	init_threads(&data);
	wait_threads(&data);
	destroy_mutexes(&data);
	free_fixed_arena_data(&arena_data);
	return (0);
}
