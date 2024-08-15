
#include "philo.h"

long	get_time(t_time time_code)
{
	struct time_val;

	if (gettimeofday(&time_val, NULL))
		error_exit(RED"ERROR!\ngettimeofday failuer."RESET);
	if (time_code == SEC)
		return (time_val.tv_sec + (time_val.tv_usec / 1e6));
	else if (time_code == MILISEC)
		return ((time_val.tv_sec * 1e3) + (time_val.tv_usec / 1e3));
	else if (time_code == MICROSEC)
		return ((time_val.tv_sec * 1e6) + time_val.tv_usec);
	else
		error_exit(RED"ERROR!\nerror in \'get_time()\' input"RESET);
	return (666);
}

void	error_exit(const char *error_str)
{
	printf("%s\n", error_str);
	exit(EXIT_FAILURE);
}

