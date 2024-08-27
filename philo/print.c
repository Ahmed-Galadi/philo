/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 23:38:38 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/27 16:52:09 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state_debug(t_philo *philo, t_state state, long time_passed)
{
	if (state == FORK1_TAKE && !is_sim_end(philo->data))
		printf("%ld %d has taken a fork\n",
			time_passed, philo->philo_id);
	else if (state == FORK2_TAKE && !is_sim_end(philo->data))
		printf("%ld %d has taken a fork\n",
			time_passed, philo->philo_id);
	else if (state == EATING && !is_sim_end(philo->data))
		printf("%ld %d is eating\n",
			time_passed, philo->philo_id);
	else if (state == THINKING && !is_sim_end(philo->data))
		printf("%ld %d is thinking\n",
			time_passed, philo->philo_id);
	else if (state == SLEEPING && !is_sim_end(philo->data))
		printf("%ld %d is sleeping\n",
			time_passed, philo->philo_id);
	else if (state == DEATH)
		printf("%ld %d is dead\n", time_passed, philo->philo_id);
}

void	print_state(t_philo *philo, t_state state, bool debug)
{
	long	time_passed;

	time_passed = get_time(MILISEC) - philo->data->start_simulation;
	if (philo->is_full)
		return ;
	handle_mutex(&philo->data->mutex_print, LOCK);
	if (debug)
		print_state_debug(philo, state, time_passed);
	else
	{
		if ((state == FORK1_TAKE || state == FORK2_TAKE)
			&& !is_sim_end(philo->data))
			printf(FORK_MSG, time_passed, philo->philo_id);
		else if (state == EATING && !is_sim_end(philo->data))
			printf(EATING_MSG, time_passed, philo->philo_id);
		else if (state == THINKING && !is_sim_end(philo->data))
			printf(THINKING_MSG, time_passed, philo->philo_id);
		else if (state == SLEEPING && !is_sim_end(philo->data))
			printf(SLEEPING_MSG, time_passed, philo->philo_id);
		else if (state == DEATH)
			printf(DEATH_MSG, time_passed, philo->philo_id);
	}
	handle_mutex(&philo->data->mutex_print, UNLOCK);
}
