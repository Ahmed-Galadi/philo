/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:47:59 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/28 21:16:58 by agaladi          ###   ########.fr       */
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
		if (!data)
			return (EXIT_FAILURE);
		if (parse_input_data(&data, argv) == -1)
			return (error_exit(PARSE_ERROR_MSG), EXIT_FAILURE);
		if (!data_init(data))
			return (EXIT_FAILURE);
		start_dining(data);
		clean(&data);
	}
	else
		error_exit(INP_ERR_MSG);
	return (0);
}
