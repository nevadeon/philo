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

void	init_data(t_data *d, t_allocator *arena, int argc, char const *argv[])
{
	d->nb_philos = atou(argv[NB_OF_PHILO_INDEX]);
	d->time_to_die_ms = atou(argv[TIME_TO_DIE_INDEX]);
	d->time_to_eat_ms = atou(argv[TIME_TO_EAT_INDEX]);
	d->time_to_sleep_ms = atou(argv[TIME_TO_SLEEP_INDEX]);
	if (argc == 6)
		d->nb_meals_to_eat = atou(argv[NB_TIME_PHILO_MUST_EAT_INDEX]);
	else
		d->nb_meals_to_eat = -1;
	d->philos = mem_alloc(arena, d->nb_philos * sizeof(pthread_t));
	d->reapers = mem_alloc(arena, d->nb_philos * sizeof(pthread_t));
	d->forks = mem_alloc(arena, d->nb_philos * sizeof(pthread_mutex_t));
	d->args = mem_alloc(arena, d->nb_philos * sizeof(t_thread_arg));
	d->id_width = _compute_width(d->nb_philos);
	d->start_time_ms = get_time_ms();
	d->stop_simulation = false;
	d->done_count = 0;
	_init_args(d);
}
