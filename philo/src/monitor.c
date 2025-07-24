/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:04:27 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/24 19:39:19 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_dead_think(t_philo_d *data, int index);
static int	kill_philo(t_philo_d *data, int index_dead);
static void	print_message(t_state new_state, t_guy *philo);

int	monitor(t_philo_d *data)
{
	int		index;
	int		food_left;

	food_left = -1;
	while (data->all_alive == 1 && food_left != 0)
	{
		index = -1;
		food_left = 0;
		while (++index < data->num_phil)
		{
			if (check_dead_think(data, index))
				return (1);
			food_left += (data->philos[index]).meals_left;
		}
	}
	return (1);
}

static int	check_dead_think(t_philo_d *data, int index)
{
	time_t	time_c;

	pthread_mutex_lock(&(data->mutex_state[index]));
	time_c = c_time();
	if (time_c >= (data->philos[index]).die_t
		&& (data->philos[index]).meals_left != 0)
	{
		pthread_mutex_unlock(&(data->mutex_state[index]));
		return (kill_philo(data, index));
	}
	else
		pthread_mutex_unlock(&(data->mutex_state[index]));
	pthread_mutex_lock(&(data->mutex_state[index]));
	if (time_c >= (data->philos[index]).think_t
		&& (data->philos[index]).state == SLEEP)
	{
		pthread_mutex_unlock(&(data->mutex_state[index]));
		message(THINK, &(data->philos[index]));
	}
	else
		pthread_mutex_unlock(&(data->mutex_state[index]));
	return (0);
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
	return (1);
}

void	message(t_state new_state, t_guy *philo)
{

	pthread_mutex_lock(philo->state_m);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(philo->state_m);
		return ;
	}
	pthread_mutex_lock(philo->write_m);
	print_message(new_state, philo);
	pthread_mutex_unlock(philo->write_m);
	pthread_mutex_unlock(philo->state_m);
}

static void	print_message(t_state new_state, t_guy *philo)
{
	time_t	curr_time;

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
	if (new_state != FORK)
		philo->state = new_state;
}
