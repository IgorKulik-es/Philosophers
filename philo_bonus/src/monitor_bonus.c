/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:04:27 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/30 15:49:30 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

static int	check_dead_think_b(t_guy *philo, t_philo_d *data);

void	wait_sems_pids(t_philo_d *data)
{
	int	index;

	index = 0;
	while (index < data->num_phil)
	{
		sem_wait(data->sem_fb);
		index++;
	}
	while (index > 0)
	{
		sem_post(data->sem_stop);
		index--;
	}
	while (index < data->num_phil)
	{
		waitpid(data->pids[index], NULL, 0);
		index++;
	}
}

void	*wait_poison(void *philo_arg)
{
	t_guy	*philo;

	philo = (t_guy *)philo_arg;
	sem_wait(philo->sem_poison);
	philo->state = DEAD;
	if (philo->data->num_phil == 1)
		sem_post(philo->sem_forks);
	return (NULL);
}

void	*monitor_dead(void *philo_arg)
{
	t_guy		*philo;
	t_philo_d	*data;

	philo = (t_guy *)philo_arg;
	data = philo->data;
	while (philo->state != DEAD && philo->meals_left != 0)
	{
		usleep(REF_RATE);
		if (check_dead_think_b(philo, data))
			return (NULL);
	}
	return (NULL);
}

static int	check_dead_think_b(t_guy *philo, t_philo_d *data)
{
	time_t	time_c;

	time_c = c_time();
	if (time_c >= philo->die_t
		&& philo->meals_left != 0)
	{
		message_b(DEAD, philo);
		sem_fill(data, data->sem_fb);
		return (EXIT_FAILURE);
	}
	if (time_c >= philo->think_t
		&& philo->state == SLEEP)
		message_b(THINK, philo);
	return (EXIT_SUCCESS);
}

void	message_b(t_state new_state, t_guy *philo)
{
	time_t	curr_time;

	if (philo->state == DEAD)
		return ;
	if (new_state != FORK)
		philo->state = new_state;
	curr_time = c_time() - philo->start;
	if (new_state == FORK)
		printf(C_CYN "%ld %d has taken a fork\n" C_RESET,
			curr_time, philo->index + 1);
	if (new_state == EAT)
		printf(C_YEL "%ld %d is eating\n" C_RESET, curr_time, philo->index + 1);
	if (new_state == SLEEP)
		printf(C_GRN "%ld %d is sleeping\n" C_RESET,
			curr_time, philo->index + 1);
	if (new_state == THINK)
		printf(C_MAG "%ld %d is thinking\n" C_RESET,
			curr_time, philo->index + 1);
	if (new_state == DEAD)
		printf(C_RED "%ld %d is dead\n" C_RESET, curr_time, philo->index + 1);
}
