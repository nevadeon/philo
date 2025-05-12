#include "philo.h"

bool	stop_simulation(t_data *data)
{
	bool	value;

	pthread_mutex_lock(&data->stop_simulation_mutex);
	value = data->stop_simulation;
	pthread_mutex_unlock(&data->stop_simulation_mutex);
	return (value);
}

void	set_stop_simulation(t_data *data, bool value)
{
	pthread_mutex_lock(&data->stop_simulation_mutex);
	data->stop_simulation = value;
	pthread_mutex_unlock(&data->stop_simulation_mutex);
}

bool	is_done_eating(t_thread_arg *arg)
{
	bool	value;

	pthread_mutex_lock(&arg->is_done_eating_mutex);
	value = arg->is_done_eating;
	pthread_mutex_unlock(&arg->is_done_eating_mutex);
	return (value);
}

void	set_is_done_eating(t_thread_arg *arg, bool value)
{
	pthread_mutex_lock(&arg->is_done_eating_mutex);
	arg->is_done_eating = value;
	pthread_mutex_unlock(&arg->is_done_eating_mutex);
}

void	update_last_meal(t_thread_arg *arg)
{
	pthread_mutex_lock(&arg->last_meal_mutex);
	arg->last_meal_ms = get_time_ms();
	pthread_mutex_unlock(&arg->last_meal_mutex);
}
