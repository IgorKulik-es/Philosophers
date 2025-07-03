/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:13:22 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/03 18:38:55 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	try_to_eat(t_guy *philo);
static void	grab_forks(t_guy *philo);
static void	update_state(t_guy *philo);

void	*life_cycle(void *input)
{
	t_guy	*philo;

	philo = (t_guy *)input;
	while (philo->state != DEAD && philo->meals_left != 0)
	{
		pthread_mutex_lock(philo->state_m);
		if (philo->state == THINK || philo->state == SLEEP)
		{
			pthread_mutex_unlock(philo->state_m);
			try_to_eat(philo);
		}
		else
			pthread_mutex_unlock(philo->state_m);
		pthread_mutex_lock(philo->state_m);
		if (philo->state == EAT)
		{
			pthread_mutex_unlock(philo->state_m);
			message(SLEEP, philo);
			usleep(philo->life->sleep * MILLISEC);
		}
		else
			pthread_mutex_unlock(philo->state_m);
	}
	return (NULL);
}

static void	try_to_eat(t_guy *philo)
{
	grab_forks(philo);
	update_state(philo);
	pthread_mutex_lock(philo->state_m);
	if (philo->state != DEAD)
	{
		pthread_mutex_unlock(philo->state_m);
		usleep(philo->life->eat * MILLISEC);
	}
	else
		pthread_mutex_unlock(philo->state_m);
	if (philo->left_m != philo->right_m)
	{
		*(philo->fork_l) = true;
		*(philo->fork_r) = true;
		pthread_mutex_unlock(philo->right_m);
	}
	pthread_mutex_unlock(philo->left_m);
}

static void	update_state(t_guy *philo)
{
	if (philo->right_m != philo->left_m)
	{
		message(EAT, philo);
		pthread_mutex_lock(philo->state_m);
		if (philo->meals_left > 0)
			(philo->meals_left)--;
		philo->die_t = c_time() + philo->life->die;
		philo->think_t = c_time() + philo->life->eat + philo->life->sleep;
		pthread_mutex_unlock(philo->state_m);
	}
}

static void	grab_forks(t_guy *philo)
{
	pthread_mutex_lock(philo->left_m);
	if (*(philo->fork_l))
		message(FORK, philo);
	*(philo->fork_l) = false;
	if (philo->right_m != philo->left_m)
	{
		pthread_mutex_lock(philo->right_m);
		*(philo->fork_r) = false;
		message(FORK, philo);
	}
}
