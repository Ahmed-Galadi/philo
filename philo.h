/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:35:48 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/26 23:38:21 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>

// Define color codes
# define RESET       "\033[0m"
# define RED         "\033[31m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m"
# define MAGENTA     "\033[35m"
# define CYAN        "\033[36m"
# define WHITE       "\033[37m"

// Define background colors
# define RED_BG      "\033[41m"
# define GREEN_BG    "\033[42m"
# define YELLOW_BG   "\033[43m"
# define BLUE_BG     "\033[44m"
# define MAGENTA_BG  "\033[45m"
# define CYAN_BG     "\033[46m"
# define WHITE_BG    "\033[47m"

// Define text attributes
# define BOLD        "\033[1m"
# define UNDERLINE   "\033[4m"

// [eat, sleep, think] messages
# define FORK_MSG "\033[1m%ld \033[44m%d\033[0m\033[34m\033[1m \
has taken a fork (っ'-')‎𐂐\033[0m\n"

# define EATING_MSG "\033[1m\033[4m%ld \033[0m\033[1m\033[42m\
%d\033[0m \033[32m\033[1m\033[4mis eating ‎𐂐◯𓇋(๑ᵔ⤙ᵔ๑)\033[0m\n"

# define SLEEPING_MSG "\033[1m%ld \033[45m%d\033[0m \033[35m\033[1m\
is sleeping ꒰꒡⌓꒡꒱zzz\033[0m\n"

# define THINKING_MSG "\033[1m%ld \033[43m%d\033[0m\
 \033[33m\033[1mis thinking (≖_≖ )?\033[0m\n"

# define DEATH_MSG "\033[4m%ld \033[0m\033[1m\033[41m\
%d\033[0m \033[31m\033[1m\033[4mis dead \033[0m\033[1m\033[31m(×_×)\033[0m\n"

# define INP_ERR_MSG "\033[31mWrong Input:\n\
\033[0m\033[1m\033[4mPlease Enter:\
\033[0m\033[32m ./philo <philo_nbr> <time_to_die> \
<time_to_eat> <time_to_sleep> [meals]\033[0m"

# define DEBUG 0

typedef enum e_opcode
{
	CREATE,
	DESTROY,
	INIT,
	JOIN,
	DETACH,
	LOCK,
	UNLOCK
}			t_opcode;

typedef enum e_time
{
	MICROSEC,
	MILISEC,
	SEC,
}			t_time;

typedef pthread_mutex_t	t_pmtx;
typedef struct s_data	t_data;
// Fork
typedef struct s_fork
{
	t_pmtx		fork;
	int			fork_id;
}				t_fork;
// philosophers state
typedef enum e_state
{
	SLEEPING,
	EATING,
	THINKING,
	FORK1_TAKE,
	FORK2_TAKE,
	DEATH,
}			t_state;
// Philosopher
typedef struct s_philo
{
	int			philo_id;
	int			meals_count;
	bool		is_full;
	long		last_meal;
	t_fork		*fork_1;
	t_fork		*fork_2;
	pthread_t	thread_id;
	t_pmtx		philo_mutex;
	t_data		*data;
}				t_philo;

// Data Container
struct	s_data
{
	long		philo_nbr;
	long		time_to_die;
	long		time_to_sleep;
	long		time_to_eat;
	long		max_meals;
	long		start_simulation;
	bool		end_simulation;
	bool		is_threads_ready;
	pthread_t	monitor_thread;
	long		running_threads_count;
	t_pmtx		mutex_table;
	t_pmtx		mutex_print;
	t_fork		*forks;
	t_philo		*philos;
};
// error handler
void	error_exit(const char *error_str);
// input parse
void	parse_input_data(t_data **data, char **argv);
// costum functions
void	*cstm_malloc(size_t bites);
void	data_init(t_data *data);
void	handle_thread(pthread_t *thread,
			void *(*f)(void *), void *data, t_opcode code);
void	handle_mutex(t_pmtx *mutex, t_opcode code);
bool	is_sim_end(t_data *data);
bool	get_bool_mutex(t_pmtx *mutex, bool *to_get);
void	set_bool_mutex(t_pmtx *mutex, bool *to_set, bool val);
void	set_long_mutex(t_pmtx *mutex, long *to_set, long val);
long	get_long_mutex(t_pmtx *mutex, long *to_get);
void	set_bool_mutex(t_pmtx *mutex, bool *to_set, bool val);
long	get_time(t_time time_code);
void	wait_threads(t_data *data);
void	accurate_usleep(long usecond, t_data *data);
void	print_state(t_philo *philo, t_state state, bool debug);
void	start_dining(t_data *data);
bool	is_allthreads_runing(t_pmtx *mutex, long *threads, long philo_nbr);
void	long_pp(t_pmtx *mutex, long *count);
void	*monitoring(void *data);
void	thinking(t_philo *philo, bool is_sync);
void	desync_philos(t_philo *philo);

#endif
