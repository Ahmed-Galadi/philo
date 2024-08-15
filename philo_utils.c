#include "philo.h"

void set_bool_mutex(t_pmtx *mutex, bool *to_set, bool val)
{
	handle_mutex(mutex, LOCK);
	*to_set = val;
	handle_mutex(mutex, UNLOCK);
}

bool get_bool_mutex(t_pmtx *mutex, bool *to_get)
{
	bool output;

	handle_mutex(mutex, LOCK);
	output = *to_get;
	handle_mutex(mutex, UNLOCK);
	return (output);
}

void	set_long_mutex(t_pmtx *mutex, long *to_set, bool val)
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

bool is_sim_end(t_data *data)
{
	return (get_bool_mutex(data->mutex_table, &data->end_simulation));
}
