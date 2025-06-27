/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:13:22 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/27 19:26:00 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	life_cycle(t_philo_d *data, int index);
static void	try_to_eat(t_guy *philo);
static void	grab_forks(t_guy *philo);

int	give_birth(t_philo_d *data, int index)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		data->sem_ptr = sem_open(data->sem_name, O_RDONLY);
		if (data->sem_ptr == SEM_FAILED)
		{
			clean_all(data, 0);
			exit(EXIT_FAILURE);
		}
		life_cycle(data, index);
		clean_all(data, EXIT_SUCCESS);
		exit(EXIT_SUCCESS);
	}
	else
		data->pids[index] = pid;

}
















void	life_cycle(t_philo_d *data, int index)
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
	pthread_mutex_lock(philo->state_m);
	if (philo->state != DEAD)
	{
		pthread_mutex_unlock(philo->state_m);
		usleep(philo->life->eat * MILLISEC);
	}
	else
		pthread_mutex_unlock(philo->state_m);
	if (philo->left_m != philo->right_m)
		*(philo->fork_l) = true;
	if (philo->left_m != philo->right_m)
		*(philo->fork_r) = true;
	pthread_mutex_unlock(philo->right_m);
	pthread_mutex_unlock(philo->left_m);
}

static void	grab_forks(t_guy *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->left_m);
		if (*(philo->fork_l))
			message(FORK, philo);
		*(philo->fork_l) = false;
	}
	if (philo->right_m != philo->left_m)
	{
		pthread_mutex_lock(philo->right_m);
		*(philo->fork_r) = false;
		message(FORK, philo);
	}
	if (philo->index % 2 == 1)
	{
		pthread_mutex_lock(philo->left_m);
		*(philo->fork_l) = false;
		message(FORK, philo);
	}
}
