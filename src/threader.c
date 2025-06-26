/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:13:22 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/26 20:01:17 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	try_to_eat(t_guy *philo);
static int	kill_philo(t_philo_d *data, int index_dead);
static void	grab_forks(t_guy *philo);

void	*life_cycle(void *input)
{
	t_guy	*philo;

	philo = (t_guy *)input;
	while (philo->state != DEAD)
	{
		if (philo->state == THINK || philo->state == SLEEP)
			try_to_eat(philo);
		if (philo->state == EAT)
		{
			message(SLEEP, philo);
			usleep(philo->life->sleep * MILLISEC);
		}
	}
	return (NULL);
}

static void	try_to_eat(t_guy *philo)
{
	grab_forks(philo);
	message(EAT, philo);
	philo->die_t = c_time() + philo->life->die;
	philo->think_t = c_time() + philo->life->eat + philo->life->sleep;
	if (philo->state == EAT)
		usleep(philo->life->eat * MILLISEC);
	*(philo->fork_l) = true;
	*(philo->fork_r) = true;
	pthread_mutex_unlock(philo->right_m);
	pthread_mutex_unlock(philo->left_m);
}

void	message(t_state new_state, t_guy *philo)
{
	time_t	curr_time;

	pthread_mutex_lock(philo->state_m);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(philo->state_m);
		return ;
	}
	curr_time = c_time() - philo->start;
	if (new_state == FORK)
		printf("%ld %d has taken a fork\n", curr_time, philo->index + 1);
	if (new_state == EAT)
		printf("%ld %d is eating\n", curr_time, philo->index + 1);
	if (new_state == SLEEP)
		printf("%ld %d is sleeping\n", curr_time, philo->index + 1);
	if (new_state == THINK)
		printf("%ld %d is thinking\n", curr_time, philo->index + 1);
	if (new_state == DEAD)
		printf("%ld %d is dead\n", curr_time, philo->index + 1);
	if (new_state != FORK)
		philo->state = new_state;
	pthread_mutex_unlock(philo->state_m);
}

int	monitor(t_philo_d *data)
{
	int		index;
	time_t	time_c;

	while (data->all_alive == 1)
	{
		usleep(REF_RATE);
		index = -1;
		while (++index < data->num_phil)
		{
			time_c = c_time();
			if (time_c >= (data->philos[index]).die_t)
				return (kill_philo(data, index));
			if (time_c >= (data->philos[index]).think_t
				&& (data->philos[index]).state == SLEEP)
				message(THINK, &(data->philos[index]));
		}
	}
	return (1);
}

static void	grab_forks(t_guy *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->left_m);
		*(philo->fork_l) = false;
		message(FORK, philo);
	}
	pthread_mutex_lock(philo->right_m);
	*(philo->fork_r) = false;
	message(FORK, philo);
	if (philo->index % 2 == 1)
	{
		pthread_mutex_lock(philo->left_m);
		*(philo->fork_l) = false;
		message(FORK, philo);
	}
}

static int	kill_philo(t_philo_d *data, int index_dead)
{
	int	index_others;

	index_others = -1;
	message(DEAD, &(data->philos[index_dead]));
	data->all_alive = 0;
	while (++index_others < data->num_phil)
	{
		pthread_mutex_lock(&(data->mutex_state[index_others]));
		(data->philos[index_others]).state = DEAD;
		pthread_mutex_unlock(&(data->mutex_state[index_others]));
	}
	return (0);
}

