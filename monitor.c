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

bool	death(t_philo *philo)
{
	 
}

void	*monitoring(void *data)
{
	t_data	*m_data;
	int		i;

	m_data = (t_data *)data;
	while (!is_allthreads_runing(&m_data->mutex_table, &m_data->running_threads_count, m_data->philo_nbr))
		;
	while (!is_sim_end(m_data))
	{
		i = 0;
		while (i < m_data->philo_nbr && !is_sim_end(m_data))
		{
			if (death(m_data->philos + i))
			{
				set_bool_mutex(&m_data->mutex_table, &,_data->end_simulation, true);
				print_state(DEATH, m_data->philos + i, DEBUG);
			}
			i++;
		}
	}
	return (NULL);
}
