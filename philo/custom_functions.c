/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:45:49 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/26 22:42:36 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*cstm_malloc(size_t bites)
{
	void	*output;

	output = malloc(bites);
	if (!output)
		error_exit(RED"ERROR !\nAllocation failed!");
	return (output);
}

void	handle_mutex(t_pmtx *mutex, t_opcode code)
{
	if (code == LOCK)
		pthread_mutex_lock(mutex);
	else if (code == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (code == INIT)
	{
		if (pthread_mutex_init(mutex, NULL))
			error_exit(RED"ERROR!\npthread_mutex_init Failed!\n"RESET);
	}
	else if (code == DESTROY)
		pthread_mutex_destroy(mutex);
	else
		error_exit(RED"Wrong operation code for handle_mutex!"RESET);
}

void	handle_thread(
		pthread_t *thread,
		void *(*f)(void *),
		void *data, t_opcode code)
{
	if (code == CREATE)
		pthread_create(thread, NULL, f, data);
	else if (code == JOIN)
		pthread_join(*thread, NULL);
	else if (code == DETACH)
		pthread_detach(*thread);
	else
		error_exit(RED"ERROR!\nthread_handle: wrong code, \
		use <CREATE>, <JOIN> or <DETACH>"RESET);
}

void	desync_philos(t_philo *philo)
{
	if (philo->data->philo_nbr % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			accurate_usleep(3e4, philo->data);
	}
	else
		thinking(philo, true);
}
