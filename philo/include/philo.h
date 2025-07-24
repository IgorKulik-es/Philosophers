/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:34:19 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/24 18:51:51 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# define MILLISEC 1000
# define REF_RATE 100
# define C_RED "\x1B[31m"
# define C_GRN "\x1B[32m"
# define C_YEL "\x1B[33m"
# define C_BLU "\x1B[34m"
# define C_MAG "\x1B[35m"
# define C_CYN "\x1B[36m"
# define C_RESET "\x1B[0m"

typedef enum e_state
{
	EAT,
	SLEEP,
	THINK,
	FORK,
	DEAD
}			t_state;

typedef struct s_life_data
{
	int	die;
	int	num;
	int	eat;
	int	sleep;
	int	food;
}			t_base;

typedef struct s_one_philo
{
	t_state			state;
	time_t			start;
	time_t			think_t;
	time_t			die_t;
	int				meals_left;
	int				index;
	t_base			*life;
	pthread_mutex_t	*left_m;
	pthread_mutex_t	*right_m;
	pthread_mutex_t	*state_m;
	pthread_mutex_t	*write_m;
	bool			*fork_l;
	bool			*fork_r;
}				t_guy;

typedef struct s_philo_data
{
	int				num_phil;
	int				all_alive;
	bool			*forks;
	pthread_t		*threads;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	*mutex_state;
	pthread_mutex_t	mutex_write;
	t_guy			*philos;
	t_base			life;
	time_t			start;
}				t_philo_d;

int		ft_atoi(const char *nptr);
time_t	c_time(void);
int		read_values(t_philo_d *data, int argc, char **argv);
int		initialize_metadata(t_philo_d *data);
int		clean_all(t_philo_d *data, int error_code);
void	*life_cycle(void *input);
void	message(t_state new_state, t_guy *philo);
int		monitor(t_philo_d *data);
void	initialize_threads(t_philo_d *data);
void	join_destroy(t_philo_d *data);

#endif
