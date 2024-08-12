
#include "philo.h"

static void	init_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->data->philo_nbr;
	if (philo->philo_id % 2 == 0)
	{
		philo->fork_1 = &forks[philo_position];
		philo->fork_2 = &forks[(philo_position + 1) % philo_nbr];
	}
	else 
	{
		philo->fork_1 = &forks[(philo_position + 1) % philo_nbr];
		philo->fork_2 = &forks[philo_position];
	}
}

static void	philo_init(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->philo_nbr)
	{
		philo = data->philos + i;
		philo->philo_id = i + 1;
		philo->is_full = false;
		philo->meals_count = 0;
		philo->data = data;
		init_forks(philo, data->forks, i);
		i++;
	}
}

void	data_init(t_data **data)
{
	int		i;

	i = 0;
	(*data)->end_simulation = false;
	(*data)->philos = cstm_malloc(sizeof(t_philo) * (*data)->philo_nbr);
	(*data)->forks = cstm_malloc(sizeof(t_fork) * (*data)->philo_nbr);
	while (i < (*data)->philo_nbr)
	{
		handle_mutex(&(*data)->forks[i].fork, INIT);
		(*data)->forks[i].fork_id = i;	
		i++;
	}
	philo_init(*data);
}
