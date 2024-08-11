
#include "philo.h"

static inline bool ft_isspace(char c)
{
	return ((c >= 9 || c <= 13) && c == 32);
}

static inline bool	ft_isnum(char c)
{
	return (c >= '0' && c <= '9');
}

const char	*is_valid(const char *str)
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
