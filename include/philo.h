#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include "allocator.h"
# include "block_allocator.h"

# define NB_OF_PHILO_INDEX 1
# define TIME_TO_DIE_INDEX 2
# define TIME_TO_EAT_INDEX 3
# define TIME_TO_SLEEP_INDEX 4
# define NB_TIME_PHILO_MUST_EAT_INDEX 5

typedef struct s_thread_arg	t_thread_arg;

typedef enum e_error
{
	ERR_MIN,
	ERR_USAGE,
	ERR_NON_NUMERICAL_INPUT,
	ERR_TOO_MANY_PHILO,
	ERR_MUTEX_INIT_FAIL,
	ERR_THREAD_INIT_FAIL,
	ERR_FAILED_ALLOCATION,
	ERR_MAX
}	t_error;

typedef struct s_data
{
	pthread_mutex_t	stop_simulation_mutex;
	pthread_mutex_t	done_count_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	pthread_t		*philos;
	pthread_t		*reapers;
	t_thread_arg	*args;
	long			start_time_ms;
	int				id_width;
	int				time_to_eat_ms;
	int				time_to_sleep_ms;
	int				time_to_die_ms;
	int				nb_philos;
	int				nb_meals_to_eat;
	int				done_count;
	bool			stop_simulation;
}	t_data;

typedef struct s_thread_arg
{
	t_data			*data;
	pthread_mutex_t	last_meal_mutex;
	long			last_meal_ms;
	int				id;
}	t_thread_arg;

//main
t_data	make_data(t_alloc *arena, int argc, char const *argv[]);
void	init_threads(t_data *data);
void	init_mutexes(t_data *data);
void	destroy_mutexes(t_data *data);
void	wait_threads(t_data *data);

//routines
void	*philo_routine(void *_arg);
void	*reaper_routine(void *_arg);

//helper functions
void	update_last_meal(t_thread_arg *arg);
bool	stop_simulation(t_data *data);
void	set_stop_simulation(t_data *data, bool value);

//utils
int		atou(const char *s);
void	exit_error(t_error error_code);
long	get_time_ms(void);
void	msleep(long time_to_sleep_ms);
void	print_philo_status(t_data *data, int id, const char *status);
void	print_philo_status2(t_data *data, int id, const char *status);

#endif
