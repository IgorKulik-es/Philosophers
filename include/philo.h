/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:34:19 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/24 20:16:57 by ikulik           ###   ########.fr       */
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
# define MILLISEC 1000

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
	time_t			eat_t;
	time_t			sleep_t;
	time_t			think_t;
	time_t			die_t;
	int				meals_had;
	int				index;
	t_base			*life;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
}				t_guy;


typedef struct s_philo_data
{
	int				num_phil;
	int				all_alive;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
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

#endif
