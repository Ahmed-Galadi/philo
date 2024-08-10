/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:35:48 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/10 10:02:12 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

typedef pthread_mutex_t t_pmtx;
typedef s_data t_data;
// Fork
typedef struct	s_fork
{
	t_pmtx		fork;
	int			fork_id;
}				t_fork;

// Philosopher
typedef struct	s_philo
{
	int			philo_id;
	int			meals_count;
	bool		is_full;
	long		last_meal;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_data		*data;
}				t_philo;

// Data Container
struct	s_data
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_sleep;
	long	time_to_eat;
	long	max_meals;
	long	start_simulation;
	bool	end_simulation;
	t_fork	*forks;
	t_philo	*philos;
};

#endif
