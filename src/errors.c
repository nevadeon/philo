#include "philo.h"

const char	*get_error_message(t_error error_code)
{
	static const char	*message[] = {\
		[ERR_MIN] = "get_error_message was called with invalid index", \
		[ERR_USAGE] = "usage ./philo number_of_philosophers time_to_die \
			time_to_eat time_to_sleep \
			[number_of_times_each_philosopher_must_eat]", \
		[ERR_NON_NUMERICAL_INPUT] = "Program only accepts positive integers as \
			parameters", \
		[ERR_TOO_MANY_PHILO] = "200 philosophers at max", \
		[ERR_MUTEX_INIT_FAIL] = "failed to initialise mutex", \
		[ERR_THREAD_INIT_FAIL] = "failed to create thread", \
		[ERR_FAILED_ALLOCATION] = "failed to allocate memory" \
	};

	if (error_code >= ERR_MAX || error_code <= ERR_MIN)
		return (message[ERR_MIN]);
	return (message[error_code]);
}

void	exit_error(t_error error_code)
{
	fprintf(stderr, "error: %s\n", get_error_message(error_code));
	exit(error_code);
}
