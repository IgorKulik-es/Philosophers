/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:47:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/28 17:55:12 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	initialize_philo(t_philo_d *data, int ind);

int	read_values(t_philo_d *data, int argc, char **argv)
{
	if ((argc != 5) && (argc != 6))
		return (1);
	data->life.num = ft_atoi(argv[1]);
	data->num_phil = data->life.num;
	data->life.die = ft_atoi(argv[2]);
	data->life.eat = ft_atoi(argv[3]);
	data->life.sleep = ft_atoi(argv[4]);
	data->life.food = -1;
	if (argc == 6)
		data->life.food = ft_atoi(argv[5]);
	if (data->num_phil < 1 || data->life.die < 1
		|| (data->life.food < 1 && argc == 6))
		return (1);
	return (0);
}

int	initialize_metadata_b(t_philo_d *data)
{
	data->all_alive = 1;
	data->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0777, data->num_phil);
	data->sem_alive = sem_open(SEM_ALIVE, O_CREAT, 0777, 0);
	if (data->sem_forks == SEM_FAILED || data->sem_alive == SEM_FAILED)
		return (clean_parent(data, EXIT_FAILURE));
	data->pids = NULL;
	data->pids = malloc(data->num_phil * sizeof(int));
	if (data->pids == NULL)
		return (clean_parent(data, EXIT_FAILURE));
	data->start = c_time();
	return (EXIT_SUCCESS);
}

void	init_philo_b(t_philo_d *data, t_guy *philo, int index)
{
	philo->start = data->start;
	philo->die_t = data->start + data->life.die;
	philo->think_t = data->start;
	philo->state = SLEEP;
	philo->meals_left = data->life.food;
	philo->index = index;
	philo->sem_forks = data->sem_forks;
	philo->sem_poison = data->sem_alive;
	philo->data = data;
}

