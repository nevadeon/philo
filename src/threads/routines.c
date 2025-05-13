#include "philo.h"

static void	_acquire_forks(t_data *data, t_thread_arg *arg)
{
	pthread_mutex_lock(&data->forks[arg->id]);
	print_philo_status(data, arg->id, "has taken a fork");
	pthread_mutex_lock(&data->forks[((arg->id + 1) % data->nb_philos)]);
	print_philo_status(data, arg->id, "has taken a fork");
}

static void	_eat_meal(t_data *data, t_thread_arg *arg, int *meals_eaten)
{
	print_philo_status(data, arg->id, "is eating       ");
	msleep(data->time_to_eat_ms);
	update_last_meal(arg);
	(*meals_eaten)++;
	pthread_mutex_unlock(&data->forks[arg->id]);
	pthread_mutex_unlock(&data->forks[((arg->id + 1) % data->nb_philos)]);
}

static void	_increment_done_eating_counter(t_data *data)
{
	pthread_mutex_lock(&data->done_count_mutex);
	data->done_count += 1;
	if (data->done_count >= data->nb_philos)
		set_stop_simulation(data, true);
	pthread_mutex_unlock(&data->done_count_mutex);
}

void	*philo_routine(void *_arg)
{
	t_thread_arg	*arg;
	t_data			*data;
	int				meals_eaten;

	arg = _arg;
	data = arg->data;
	meals_eaten = 0;
	if (data->nb_philos == 1)
		return (print_philo_status(data, arg->id, "has taken a fork"), NULL);
	if (arg->id % 2 == 0)
		usleep(500);
	while (!stop_simulation(data))
	{
		_acquire_forks(data, arg);
		_eat_meal(data, arg, &meals_eaten);
		print_philo_status(data, arg->id, "is sleeping     ");
		msleep(data->time_to_sleep_ms);
		print_philo_status(data, arg->id, "is thinking     ");
		if (meals_eaten == data->nb_meals_to_eat)
			_increment_done_eating_counter(data);
	}
	return (NULL);
}

void	*reaper_routine(void *_arg)
{
	t_thread_arg	*arg;
	t_data			*data;
	long			elapsed_time_ms;

	arg = _arg;
	data = arg->data;
	while (!stop_simulation(data))
	{
		pthread_mutex_lock(&arg->last_meal_mutex);
		elapsed_time_ms = get_time_ms() - arg->last_meal_ms;
		pthread_mutex_unlock(&arg->last_meal_mutex);
		if (elapsed_time_ms > data->time_to_die_ms)
		{
			print_philo_status(data, arg->id, "died            ");
			set_stop_simulation(data, true);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}
