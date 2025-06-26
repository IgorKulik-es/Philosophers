/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:45:19 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/24 20:07:25 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	clean_all(t_philo_d *data, int error_code)
{
	/*int	index;

	index = -1;
	while (++index < data->num_phil)
		pthread_mutex_destroy(&(data->mutex[index]));*/
	if (data->threads != NULL)
		free(data->threads);
	if (data->forks != NULL)
		free(data->forks);
	if (data->philos != NULL)
		free(data->philos);
	if (data->mutex_fork != NULL)
		free(data->mutex_fork);
	if (data->mutex_state != NULL)
		free(data->mutex_state);
	return (error_code);
}

void	join_destroy(t_philo_d *data)
{
	int	index;

	index = 0;
	while (index < data->num_phil)
	{
		pthread_join(data->threads[index], NULL);
		index++;
	}
	index = 0;
	while (index < data->num_phil)
	{
		if (data->forks[index] == false)
			pthread_mutex_unlock(&(data->mutex_state[index]));
		pthread_mutex_destroy(&(data->mutex_fork[index]));
		pthread_mutex_destroy(&(data->mutex_state[index]));
		index++;
	}
}
