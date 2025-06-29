/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:13:22 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/25 14:52:42 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	try_to_eat(t_guy *philo);

void	*life_cycle(void *input)
{
	t_guy	*philo;

	philo = (t_guy *)input;
	while (philo->state != DEAD)
	{
		if (c_time() > philo->die_t)
			message(DEAD, philo);
		if (philo->state == THINK)
			try_to_eat(philo);
		if (philo->state == EAT && c_time() > philo->sleep_t)
		{
			message(SLEEP, philo);
			pthread_mutex_unlock(philo->right_f);
			pthread_mutex_unlock(philo->left_f);
		}
		if (philo->state == SLEEP && c_time() > philo->think_t)
			message(THINK, philo);
		usleep(1000);
	}
	return (NULL);
}

void	try_to_eat(t_guy *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->left_f);
		message(FORK, philo);
	}
	pthread_mutex_lock(philo->right_f);
	message(FORK, philo);
	if (philo->index % 2 == 1)
	{
		pthread_mutex_lock(philo->left_f);
		message(FORK, philo);
	}
	message(EAT, philo);
	philo->eat_t = c_time();
	philo->die_t = philo->eat_t + philo->life->die;
	philo->sleep_t = philo->eat_t + philo->life->eat;
	philo->think_t = philo->sleep_t + philo->life->sleep;
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
	int		index_base;
	int		index_kill;
	time_t	time_c;

	index_kill = -1;
	while (data->all_alive == 1)
	{
		index_base = -1;
		while (++index_base < data->num_phil)
		{
			time_c = c_time();
			if (time_c > (data->philos[index_base]).die_t)
			{
				message(DEAD, &(data->philos[index_base]));
				data->all_alive = 0;
				while (++index_kill < data->num_phil)
					(data->philos[index_kill]).state = DEAD;
				return (0);
			}
		}
		usleep(MILLISEC);
	}
	return (1);
}

