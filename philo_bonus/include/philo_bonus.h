/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:34:19 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/30 16:26:08 by ikulik           ###   ########.fr       */
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
# include <sys/wait.h>
# include <unistd.h>
# define MILLISEC 1000
# define REF_RATE 200
# define SEM_FORKS "sem_forks"
# define SEM_STOP "sem_stopper"
# define SEM_QUEUE "sem_queue"
# define SEM_FEEDBACK "sem_all_fed"
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

typedef struct s_philo_data
{
	int				num_phil;
	int				*pids;
	sem_t			*sem_forks;
	sem_t			*sem_queue;
	sem_t			*sem_stop;
	sem_t			*sem_fb;
	t_base			life;
	time_t			start;
}				t_philo_d;

typedef struct s_one_philo
{
	t_state			state;
	time_t			start;
	time_t			think_t;
	time_t			die_t;
	int				meals_left;
	int				index;
	sem_t			*sem_forks;
	sem_t			*sem_queue;
	sem_t			*sem_poison;
	sem_t			*sem_fb;
	t_philo_d		*data;
}				t_guy;

int		ft_atoi(const char *nptr);
time_t	c_time(void);
size_t	ft_strlen(const char *s);
int		print_error(char *error);
int		read_values(t_philo_d *data, int argc, char **argv);
int		initialize_metadata_b(t_philo_d *data);
void	init_philo_b(t_philo_d *data, t_guy *philo, int index);
void	wait_sems_pids(t_philo_d *data);
int		give_birth(t_philo_d *data);
void	*monitor_dead(void *philo_arg);
void	*wait_poison(void *philo_arg);
void	sem_fill(t_philo_d *data, sem_t *sem);
void	message_b(t_state new_state, t_guy *philo);
int		clean_child(t_philo_d *data, int error_code);
int		clean_parent(t_philo_d *data, int err_code);

#endif
