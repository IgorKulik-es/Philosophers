/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:45:19 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/27 19:03:54 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	clean_all(t_philo_d *data, int error_code)
{
	sem_close(data->sem_name);
	return (error_code);
}

/* void	join_destroy(t_philo_d *data)
{
	int	index;

	index = 0;
	while (index < data->num_phil)
	{
		pthread_join(data->threads[index], NULL);
		index++;
	}
} */
