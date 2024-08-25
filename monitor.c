#include "philo.h"

bool	is_allthreads_runing(t_pmtx *mutex, long *threads, long philo_nbr)
{
	bool	output;

	output = false;
	handle_mutex(mutex, LOCK);
	if (*threads == philo_nbr)
		output = true;
	handle_mutex(mutex, UNLOCK);
	return (output);
}

static bool	death(t_philo *philo)
{
	long	time_passed;
	long	time_to_die;
	
	if (get_bool_mutex(&philo->philo_mutex, &philo->is_full))
		return (false);
	time_passed = get_time(MILISEC) - get_long_mutex(&philo->philo_mutex, &philo->last_meal);
	time_to_die = philo->data->time_to_die / 1e3;
	if (time_passed > time_to_die)
		return (true);
	return (false);
}

void	*monitoring(void *data)
{
	t_data	*m_data;
	int		i;

	m_data = (t_data *)data;
	while (!is_allthreads_runing(&m_data->mutex_table, &m_data->running_threads_count, m_data->philo_nbr))
		;
	while (1)
	{
		i = 0;
		while (i < m_data->philo_nbr && !is_sim_end(m_data))
		{
			if (death(m_data->philos + i))
			{
				set_bool_mutex(&m_data->mutex_table, &m_data->end_simulation, true);
				print_state((m_data->philos) + i, DEATH, DEBUG);
			}
			i++;
		}
	}
	return (NULL);
}
