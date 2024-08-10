
#include "philo.h"

long	ft_atol(const char *str)
{
	long	output;
	int		i;
	
	output = 0;
	i = 0;
	while (str[i])
	{
		output = (output * 10) + str[i++] - '0';
		if (output > INT_MAX)
			error_exit();	
	}
	return (output);
}

void	parse_input_data(t_data **data, char **argv)
{
	(*data)->philo_nbr = ft_atol(argv[1]);
}
