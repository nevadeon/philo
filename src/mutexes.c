#include "philo.h"

void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			exit_error(ERR_MUTEX_INIT_FAIL);
		if (pthread_mutex_init(&data->args[i].last_meal_mutex, NULL) != 0)
			exit_error(ERR_MUTEX_INIT_FAIL);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		exit_error(ERR_MUTEX_INIT_FAIL);
	if (pthread_mutex_init(&data->stop_simulation_mutex, NULL) != 0)
		exit_error(ERR_MUTEX_INIT_FAIL);
	if (pthread_mutex_init(&data->done_count_mutex, NULL) != 0)
		exit_error(ERR_MUTEX_INIT_FAIL);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->args[i].last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_simulation_mutex);
	pthread_mutex_destroy(&data->done_count_mutex);
}
