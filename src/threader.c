/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:13:22 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/25 16:46:35 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	try_to_eat(t_guy *philo);
static int	kill_philo(t_philo_d *data, int index_dead);

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
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->left_f);
		if (philo->state != DEAD)
			message(FORK, philo);
	}
	pthread_mutex_lock(philo->right_f);
	if (philo->state != DEAD)
		message(FORK, philo);
	if (philo->index % 2 == 1)
	{
		pthread_mutex_lock(philo->left_f);
		if (philo->state != DEAD)
			message(FORK, philo);
	}
	if (philo->state != DEAD)
		message(EAT, philo);
	philo->eat_t = c_time();
	philo->die_t = philo->eat_t + philo->life->die;
	philo->sleep_t = philo->eat_t + philo->life->eat;
	philo->think_t = philo->sleep_t + philo->life->sleep;
	if (philo->state == EAT)
		usleep(philo->life->eat * MILLISEC);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
}

void	message(t_state new_state, t_guy *philo)
{
	time_t	curr_time;

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

static int	kill_philo(t_philo_d *data, int index_dead)
{
	int	index_others;

	index_others = -1;
	message(DEAD, &(data->philos[index_dead]));
	data->all_alive = 0;
	while (++index_others < data->num_phil)
		(data->philos[index_others]).state = DEAD;
	return (0);
}

