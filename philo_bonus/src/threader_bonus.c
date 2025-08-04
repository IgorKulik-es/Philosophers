/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:13:22 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/04 19:22:09 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static void	life_cycle(t_philo_d *data, int index);
static void	try_to_eat(t_guy *philo);

int	give_birth(t_philo_d *data)
{
	int	pid;
	int	index;

	index = 0;
	while (index < data->num_phil)
	{
		pid = fork();
		if (pid == -1)
			return (EXIT_FAILURE);
		if (pid == 0)
		{
			life_cycle(data, index);
			clean_child(data, EXIT_SUCCESS);
			exit(EXIT_SUCCESS);
		}
		else
			data->pids[index] = pid;
		index++;
	}
	return (EXIT_SUCCESS);
}

static void	life_cycle(t_philo_d *data, int index)
{
	t_guy		philo;
	pthread_t	mon_dead_think;
	pthread_t	mon_poison;

	init_philo_b(data, &philo, index);
	pthread_create(&mon_dead_think, NULL, monitor_dead, (void *)&philo);
	pthread_create(&mon_poison, NULL, wait_poison, (void *)&philo);
	sem_wait(data->sem_write);
	while (philo.state != DEAD && philo.meals_left != 0)
	{
		if (philo.state == THINK || philo.state == SLEEP)
			try_to_eat(&philo);
		if (philo.state == EAT)
		{
			sem_post(data->sem_write);
			message_b(SLEEP, &philo);
			usleep(data->life.sleep * MILLISEC);
			sem_wait(data->sem_write);
		}
	}
	if (philo.meals_left == 0)
		sem_post(philo.sem_fb);
	sem_post(data->sem_write);
	pthread_join(mon_dead_think, NULL);
	pthread_join(mon_poison, NULL);
}

static void	try_to_eat(t_guy *philo)
{
	sem_post(philo->sem_write);
	sem_wait(philo->sem_queue);
	sem_wait(philo->sem_forks);
	message_b(FORK, philo);
	sem_wait(philo->sem_forks);
	message_b(FORK, philo);
	sem_post(philo->sem_queue);
	sem_wait(philo->sem_write);
	if (philo->state != DEAD)
	{
		if (philo->meals_left > 0)
			(philo->meals_left)--;
		philo->die_t = c_time() + philo->data->life.die;
		philo->think_t = c_time() + philo->data->life.sleep;
		sem_post(philo->sem_write);
		message_b(EAT, philo);
		usleep(philo->data->life.eat * MILLISEC);
	}
	else
		sem_post(philo->sem_write);
	sem_post(philo->sem_forks);
	sem_post(philo->sem_forks);
	sem_wait(philo->sem_write);
}
