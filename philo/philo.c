/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:47:59 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/26 23:21:49 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <fcntl.h>

void	clean(t_data **data)
{
	long	i;

	i = 0;
	while (i < (*data)->philo_nbr)
	{
		handle_mutex(&(*data)->forks[i].fork, UNLOCK);
		handle_mutex(&(*data)->forks[i].fork, DESTROY);
		i++;
	}
	i = 0;
	while (i < (*data)->philo_nbr)
	{
		handle_mutex(&(*data)->philos[i].philo_mutex, UNLOCK);
		handle_mutex(&(*data)->philos[i].philo_mutex, DESTROY);
		i++;
	}
	handle_mutex(&(*data)->mutex_print, UNLOCK);
	handle_mutex(&(*data)->mutex_print, DESTROY);
	handle_mutex(&(*data)->mutex_table, UNLOCK);
	handle_mutex(&(*data)->mutex_table, DESTROY);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc == 5 || argc == 6)
	{
		data = (t_data *)cstm_malloc(sizeof(t_data));
		parse_input_data(&data, argv);
		data_init(data);
		start_dining(data);
		clean(&data);
	}
	else
		error_exit(INP_ERR_MSG);
	return (0);
}
