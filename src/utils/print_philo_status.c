#include "philo.h"

void	print_philo_status(t_data *data, int id, const char *status)
{
	long		current_time_ms;
	static long	last_timestamp = -1;

	pthread_mutex_lock(&data->print_mutex);
	current_time_ms = get_time_ms() - data->start_time_ms;
	if (last_timestamp != current_time_ms)
	{
		printf("╚══════╩══════════════════╝\n");
		printf("╔══════╦══════════════════╗\n");
		printf("║  id  ║    time %-8ld ║\n", current_time_ms);
		printf("╠══════╬══════════════════╣\n");
	}
	printf("║ %4d ║ %s ║\n", id + 1, status);
	last_timestamp = current_time_ms;
	pthread_mutex_unlock(&data->print_mutex);
}

void	print_philo_status2(t_data *data, int id, const char *status)
{
	long	current_time_ms;

	pthread_mutex_lock(&data->print_mutex);
	current_time_ms = get_time_ms() - data->start_time_ms;
	printf("%04ld %0*d %s\n", current_time_ms, data->id_width, id + 1, status);
	pthread_mutex_unlock(&data->print_mutex);
}
