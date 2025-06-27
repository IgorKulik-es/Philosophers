/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:47:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/27 19:29:01 by ikulik           ###   ########.fr       */
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

int	initialize_metadata(t_philo_d *data)
{
	data->all_alive = 1;
	data->sem_forks = sem_open(SEM_FORKS, O_CREAT, 0777, data->num_phil);
	data->sem_alive = sem_open(SEM_ALIVE, O_CREAT, 0777, 1);
	if (data->sem_forks == SEM_FAILED)
		return (EXIT_FAILURE);
	data->pids = NULL;
	data->pids = malloc(data->num_phil * sizeof(int));
	if (data->pids == NULL)
		return (EXIT_FAILURE);
	data->start = c_time();
	return (0);
}

void	initialize_philo(t_philo_d *data, int ind)
{
	data->forks[ind] = true;
	(data->philos[ind]).state_m = &(data->mutex_state[ind]);
	(data->philos[ind]).start = data->start;
	(data->philos[ind]).die_t = data->start + data->life.die;
	(data->philos[ind]).think_t = data->start;
	(data->philos[ind]).left_m = &(data->mutex_fork[ind]);
	(data->philos[ind]).fork_l = &(data->forks[ind]);
	if (ind < data->num_phil - 1)
		(data->philos[ind]).right_m = &(data->mutex_fork[ind + 1]);
	if (ind < data->num_phil - 1)
		(data->philos[ind]).fork_r = &(data->forks[ind + 1]);
	(data->philos[ind]).state = SLEEP;
	(data->philos[ind]).meals_left = data->life.food;
	(data->philos[ind]).index = ind;
	(data->philos[ind]).life = &(data->life);
}

void	initialize_threads(t_philo_d *data)
{
	int	index;

	index = 0;
	while (index < data->num_phil)
	{
		pthread_mutex_init(&(data->mutex_fork[index]), NULL);
		pthread_mutex_init(&(data->mutex_state[index]), NULL);
		index++;
	}
	index = 0;
	while (index < data->num_phil)
	{
		pthread_create(&(data->threads[index]), NULL, life_cycle,
			(void *)&(data->philos[index]));
		index++;
	}
}
