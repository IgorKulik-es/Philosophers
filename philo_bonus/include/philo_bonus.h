/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:34:19 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/27 19:28:06 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# define MILLISEC 1000
# define REF_RATE 100
# define SEM_FORKS "sem_forks"
# define SEM_ALIVE "sem_alive"
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
}				t_guy;


typedef struct s_philo_data
{
	int				num_phil;
	int				all_alive;
	int				*pids;
	char			*sem_forks;
	sem_t			*sem_alive;
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
