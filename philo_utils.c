#include "philo.h"

void	set_bool_mutex(t_pmtx *mutex, bool *to_set, bool val)
{
	handle_mutex(mutex, LOCK);
	*to_set = val;
	handle_mutex(mutex, UNLOCK);
}

bool	get_bool_mutex(t_pmtx *mutex, bool *to_get)
{
	bool output;

	handle_mutex(mutex, LOCK);
	output = *to_get;
	handle_mutex(mutex, UNLOCK);
	return (output);
}

void	set_long_mutex(t_pmtx *mutex, long *to_set, long val)
{
	handle_mutex(mutex, LOCK);
	*to_set = val;
	handle_mutex(mutex, UNLOCK);
}

long	get_long_mutex(t_pmtx *mutex, long *to_get)
{
	long	output;

	handle_mutex(mutex, LOCK);
	output = *to_get;
	handle_mutex(mutex, UNLOCK);
	return (output);
}

void	long_pp(t_pmtx *mutex, long *count)
{
	handle_mutex(mutex, LOCK);
	*count += 1;
	handle_mutex(mutex, UNLOCK);
}
