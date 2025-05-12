#include "philo.h"

static int	_compute_width(int n)
{
	int	width;

	width = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		width++;
	}
	return (width);
}

static void	_init_args(t_data *data)
{
	t_thread_arg	*args;
	int				i;

	args = data->args;
	i = 0;
	while (i < data->nb_philos)
	{
		args[i].id = i;
		args[i].data = data;
		args[i].is_done_eating = false;
		args[i].last_meal_ms = get_time_ms();
		i++;
	}
}

t_data	make_data(t_allocator *arena, int argc, char const *argv[])
{
	int		nb_philos;
	t_data	data;

	nb_philos = atou(argv[NB_OF_PHILO_INDEX]);
	data = (t_data){
		.nb_philos = nb_philos,
		.time_to_die_ms = atou(argv[TIME_TO_DIE_INDEX]),
		.time_to_eat_ms = atou(argv[TIME_TO_EAT_INDEX]),
		.time_to_sleep_ms = atou(argv[TIME_TO_SLEEP_INDEX]),
		.philos = mem_alloc(arena, nb_philos * sizeof(pthread_t)),
		.reapers = mem_alloc(arena, nb_philos * sizeof(pthread_t)),
		.forks = mem_alloc(arena, nb_philos * sizeof(pthread_mutex_t)),
		.args = mem_alloc(arena, nb_philos * sizeof(t_thread_arg)),
		.id_width = _compute_width(nb_philos),
		.start_time_ms = get_time_ms(),
		.stop_simulation = false,
		.done_count = 0,
	};
	if (argc == 6)
		data.nb_meals_to_eat = atou(argv[NB_TIME_PHILO_MUST_EAT_INDEX]);
	else
		data.nb_meals_to_eat = -1;
	_init_args(&data);
	return (data);
}
