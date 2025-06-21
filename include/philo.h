/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:34:19 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/21 11:34:19 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef enum e_state
{
	EAT,
	SLEEP,
	THINK,
	DEAD
}			t_state;

typedef struct s_life_data
{
	int	num;
	int	eat;
	int	sleep;
	int	food;
}			t_base;

typedef struct s_one_philo
{
	t_state			state;
	time_t			l_meal;
	pthread_mutex_t *left_f;
	pthread_mutex_t *right_f;
}				t_guy;


typedef struct s_philo_data
{
	int				num_phil;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_guy			*philos;
	t_base			life;
	time_t			start;
}				t_philo_d;



int	ft_atoi(const char *nptr);


#endif