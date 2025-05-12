#include "philo.h"

int	atou(const char *s)
{
	int	result;

	while (*s == ' ' || (*s >= '\t' && *s <= '\r'))
		s++;
	result = 0;
	while (*s)
	{
		if (*s < '0' || *s > '9')
			exit_error(ERR_NON_NUMERICAL_INPUT);
		result = result * 10 + (*s - '0');
		s++;
	}
	return (result);
}
