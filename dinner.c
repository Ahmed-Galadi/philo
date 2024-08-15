
#include "philo.h"

void	wait_threads(t_data *data)
{
	while (!get_bool_mutex(&data->mutex_table, &data->is_threads_ready));
}

void	simulate_dinner(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	wait_threads(philo->data);
}

void	start_dining(t_data *data)
{
	int		i;

	i = 0;
	if (data->max_meals == 0)
		return ;
	else if (data->philo_nbr == 1)
		;
	else
	{
		while (i < data->philo_nbr)
		{
			handle_thread(&data->philos[i].thread_id, simulate_dinner, &data->philos[i], CREATE);
			i++;
		}
	}
	data->start_simulation = get_time(MILISEC);
	set_bool_mutex(&data->mutex_table, &data->is_threads_ready, true);	
}
