/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:47:59 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/25 19:49:37 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc == 5 || argc == 6)
	{
		data = (t_data *)cstm_malloc(sizeof(t_data));
		parse_input_data(&data, argv);
		data_init(data);
		start_dining(data);
		// clean(&data);
	}
	else
		error_exit(INP_ERR_MSG);
	return (0);
}
