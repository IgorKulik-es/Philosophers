/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:29:59 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/30 13:10:22 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(void)
{
	sem_unlink(SEM_ALIVE);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_QUEUE);
	return (0);
}
