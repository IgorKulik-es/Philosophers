/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:13:22 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/22 10:13:22 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	life_cycle(t_guy *philo)
{
	while (philo->state != DEAD)
	{
		if (philo->state == THINK)
		{
			if (philo->index % 2 == 0)
				pthread_mutex_lock(philo->left_f);
			pthread_mutex_lock(philo->right_f);
			if (philo->index % 2 == 1)
				pthread_mutex_lock(philo->left_f);
			message(EAT, philo->index + 1);
			usleep(philo->life->eat * 1000);
			pthread_mutex_unlock(philo->right_f);
			pthread_mutex_unlock(philo->left_f);
		}
		if ()
		message(SLEEP, philo->index);
	}

}
