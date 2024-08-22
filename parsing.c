
#include "philo.h"

static inline bool ft_isspace(char c)
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
			error_exit(RED""RESET);
		str++;
	}
	if (!ft_isnum(*str))
		error_exit(RED"ERROR!\nPlease Enter Correct Numbers !"RESET);
	output = str;
	while (ft_isnum(*str++))
		++nbr_len;
	if (nbr_len > 10)
		error_exit(RED"ERROR!\nNumber is bigger than INT_MAX !"RESET);
	return (output);
}

static long	ft_atol(const char *str)
{
	long	output;
	int		i;
	
	str = is_valid(str);
	output = 0;
	i = 0;
	while (ft_isnum(str[i]))
	{
		output = (output * 10) + (str[i++] - '0');
		if (output > INT_MAX)
			error_exit(RED"ERROR!\nNumber is bigger than INT_MAX !"RESET);	
	}
	return (output);
}

void	parse_input_data(t_data **data, char **argv)
{
	(*data)->philo_nbr = ft_atol(argv[1]);
	(*data)->time_to_die = ft_atol(argv[2]) * 1e3;
	(*data)->time_to_eat = ft_atol(argv[3]) * 1e3;
	(*data)->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if ((*data)->time_to_die < 6e4
		|| (*data)->time_to_eat < 6e4
		|| (*data)->time_to_sleep < 6e4)
		error_exit(RED"ERROR !\nValue should be major than 60ms");
	if (argv[5])
		(*data)->max_meals = ft_atol(argv[5]);
	else
		(*data)->max_meals = -1;
}







