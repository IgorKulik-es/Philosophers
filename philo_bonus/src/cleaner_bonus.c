/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:45:19 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/04 18:06:19 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	clean_child(t_philo_d *data, int error_code)
{
	sem_close(data->sem_stop);
	sem_close(data->sem_forks);
	sem_close(data->sem_queue);
	sem_close(data->sem_fb);
	sem_close(data->sem_write);
	free(data->pids);
	return (error_code);
}

int	clean_parent(t_philo_d *data, int err_code)
{
	if (data->sem_stop)
		sem_close(data->sem_stop);
	if (data->sem_stop)
		sem_unlink(SEM_STOP);
	if (data->sem_forks)
		sem_close(data->sem_forks);
	if (data->sem_forks)
		sem_unlink(SEM_FORKS);
	if (data->sem_queue)
		sem_close(data->sem_queue);
	if (data->sem_queue)
		sem_unlink(SEM_QUEUE);
	if (data->sem_fb)
		sem_close(data->sem_fb);
	if (data->sem_fb)
		sem_unlink(SEM_FEEDBACK);
	if (data->sem_write)
		sem_close(data->sem_write);
	if (data->sem_write)
		sem_unlink(SEM_WRITE);
	if (data->pids)
		free(data->pids);
	return (err_code);
}

void	sem_fill(t_philo_d *data, sem_t *sem)
{
	int	index;

	index = 0;
	while (index < data->num_phil)
	{
		sem_post(sem);
		index++;
	}
}

int	print_error(char *error)
{
	if (error == NULL)
		return (EXIT_FAILURE);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	return (EXIT_FAILURE);
}
