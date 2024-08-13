
#include "philo.h"

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
				handle_thread(&data->philos[i].thread_id, simulate_dinner, &data->philos[i], CREATE);
	}
	
}
