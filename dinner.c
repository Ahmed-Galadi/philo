
#include "philo.h"

void	wait_threads(t_data *data)
{
	while (!get_bool_mutex(&data->mutex_table, &data->is_threads_ready));
}

static void eating(t_philo *philo)
{
	handle_mutex(&philo->fork_1->fork, LOCK);
	print_state(FORK1_TAKE, philo, DEBUG);
	handle_mutex(&philo->fork_2->fork, LOCK);
	print_state(FORK2_TAKE, philo, DEBUG);

	set_long_mutex(&philo->philo_mutex, &philo->last_meal, get_time(MILISEC));
	philo->meals_count++;
	print_state(EATING, philo, DEBUG);
	accurate_usleep(philo->data->time_to_eat, philo->data);
}

void	*simulate_dinner(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	wait_threads(philo->data);
	while (!is_sim_end(philo->data))
	{
		if (philo->is_full)
			break;
		//eat
		eating(philo);
		// sleep
		print_state(SLEEPING, philo, DEBUG);
		accurate_usleep(philo->data->time_to_sleep, philo->data);
		//think
		thinking(philo);
	}
	return (NULL);
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
	i = 0;
	while (i < data->philo_nbr)
		handle_thread(&data->philos[i++].thread_id, NULL, NULL, JOIN);
}
