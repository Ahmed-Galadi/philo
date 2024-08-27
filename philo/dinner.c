/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:51:24 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/27 23:42:41 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo, bool is_sync)
{
	long	time_to_think;
	long	time_to_eat;
	long	time_to_sleep;

	if (!is_sync)
		print_state(philo, THINKING, DEBUG);
	if (philo->data->philo_nbr % 2 == 0)
		return ;
	time_to_eat = philo->data->time_to_eat;
	time_to_sleep = philo->data->time_to_sleep;
	time_to_think = time_to_eat * 2 - time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;
	accurate_usleep(time_to_think * 0.4, philo->data);
}

static void	eating(t_philo *philo)
{
	handle_mutex(&philo->fork_1->fork, LOCK);
	print_state(philo, FORK1_TAKE, DEBUG);
	handle_mutex(&philo->fork_2->fork, LOCK);
	print_state(philo, FORK2_TAKE, DEBUG);
	set_long_mutex(&philo->philo_mutex, &philo->last_meal,
		get_time(MILISEC));
	philo->meals_count++;
	print_state(philo, EATING, DEBUG);
	accurate_usleep(philo->data->time_to_eat, philo->data);
	if (philo->data->max_meals > 0
		&& philo->meals_count == philo->data->max_meals)
		set_bool_mutex(&philo->philo_mutex, &philo->is_full, true);
	handle_mutex(&philo->fork_1->fork, UNLOCK);
	handle_mutex(&philo->fork_2->fork, UNLOCK);
}

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_threads(philo->data);
	set_long_mutex(&philo->philo_mutex, &philo->last_meal, get_time(MILISEC));
	long_pp(&philo->data->mutex_table, &philo->data->running_threads_count);
	print_state(philo, FORK1_TAKE, DEBUG);
	while (!is_sim_end(philo->data))
		usleep(200);
	return (NULL);
}

void	*simulate_dinner(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	wait_threads(philo->data);
	long_pp(&philo->data->mutex_table, &philo->data->running_threads_count);
	set_long_mutex(&philo->philo_mutex, &philo->last_meal, get_time(MILISEC));
	desync_philos(philo);
	while (!is_sim_end(philo->data))
	{
		if (philo->is_full)
			break ;
		eating(philo);
		print_state(philo, SLEEPING, DEBUG);
		accurate_usleep(philo->data->time_to_sleep, philo->data);
		thinking(philo, false);
	}
	return (NULL);
}

void	start_dining(t_data *data)
{
	int		i;

	i = -1;
	data->start_simulation = get_time(MILISEC);
	if (data->max_meals == 0)
		return ;
	else if (data->philo_nbr == 1)
		handle_thread(&data->philos[0].thread_id, one_philo,
			&data->philos[0], CREATE);
	else
	{
		while (++i < data->philo_nbr)
			handle_thread(&data->philos[i].thread_id,
				simulate_dinner, &data->philos[i], CREATE);
	}
	handle_thread(&data->monitor_thread, monitoring, data, CREATE);
	set_bool_mutex(&data->mutex_table, &data->is_threads_ready, true);
	i = 0;
	while (i < data->philo_nbr)
	{
		handle_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}
