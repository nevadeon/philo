#include "philo.h"

void	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i], NULL, \
				philo_routine, &data->args[i]) != 0)
			exit_error(ERR_THREAD_INIT_FAIL);
		if (pthread_create(&data->reapers[i], NULL, \
				reaper_routine, &data->args[i]) != 0)
			exit_error(ERR_THREAD_INIT_FAIL);
		i++;
	}
}

void	wait_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i], NULL);
		pthread_join(data->reapers[i], NULL);
		i++;
	}
}
