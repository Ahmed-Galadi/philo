/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:46:08 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/28 21:15:52 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static inline bool	ft_isnum(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*is_valid(const char *str)
{
	const char	*output;
	int			nbr_len;

	nbr_len = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (NULL);
		str++;
	}
	if (!ft_isnum(*str))
		return (NULL);
	output = str;
	while (ft_isnum(*str++))
		++nbr_len;
	if (nbr_len > 10)
		return (NULL);
	return (output);
}

static long	ft_atol(const char *str)
{
	long	output;
	int		i;

	str = is_valid(str);
	if (!str)
		return (-1);
	output = 0;
	i = 0;
	while (ft_isnum(str[i]))
	{
		output = (output * 10) + (str[i++] - '0');
		if (output > INT_MAX)
			return (-1);
	}
	return (output);
}

int	parse_input_data(t_data **data, char **argv)
{
	(*data)->philo_nbr = ft_atol(argv[1]);
	(*data)->time_to_die = ft_atol(argv[2]) * 1e3;
	(*data)->time_to_eat = ft_atol(argv[3]) * 1e3;
	(*data)->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if ((*data)->philo_nbr <= 0
		|| (*data)->time_to_die == -1
		|| (*data)->time_to_eat == -1
		|| (*data)->time_to_sleep == -1)
		return (-1);
	if ((*data)->time_to_die < 6e4
		|| (*data)->time_to_eat < 6e4
		|| (*data)->time_to_sleep < 6e4)
		return (-1);
	if (argv[5])
	{
		(*data)->max_meals = ft_atol(argv[5]);
		if ((*data)->max_meals == -1)
			return (-1);
	}
	else
		(*data)->max_meals = -1;
	return (0);
}
