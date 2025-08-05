/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:47:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/05 19:57:40 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	initialize_philo(t_philo_d *data, int ind);

int	read_values(t_philo_d *data, int argc, char **argv)
{
	if ((argc != 5) && (argc != 6))
		return (EXIT_FAILURE);
	data->life.num = ft_atoi(argv[1]);
	data->num_phil = data->life.num;
	data->life.die = ft_atoi(argv[2]);
	data->life.eat = ft_atoi(argv[3]);
	data->life.sleep = ft_atoi(argv[4]);
	data->life.food = -1;
	if (argc == 6)
		data->life.food = ft_atoi(argv[5]);
	if (data->num_phil < 1 || data->life.die < 1
		|| data->life.eat < 1 || data->life.sleep < 1
		|| (data->life.food < 1 && argc == 6))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	initialize_metadata(t_philo_d *data)
{
	int	index;

	index = -1;
	data->all_alive = 1;
	data->threads = NULL;
	data->philos = NULL;
	data->forks = NULL;
	data->mutex_fork = NULL;
	data->mutex_state = NULL;
	data->threads = (pthread_t *)malloc(data->num_phil * sizeof(pthread_t));
	data->mutex_fork = (pthread_mutex_t *)malloc(data->num_phil
			* sizeof(pthread_mutex_t));
	data->philos = (t_guy *)malloc(data->num_phil * sizeof(t_guy));
	data->forks = (bool *)malloc(data->num_phil * sizeof(bool));
	data->mutex_state = malloc(data->num_phil * sizeof(pthread_mutex_t));
	if (data->forks == NULL || data->philos == NULL || data->threads == NULL
		|| data->mutex_fork == NULL || data->mutex_state == NULL)
		return (clean_all(data, EXIT_FAILURE));
	data->start = c_time();
	while (++index < data->num_phil)
		initialize_philo(data, index);
	(data->philos[data->num_phil - 1]).right_m = &(data->mutex_fork[0]);
	(data->philos[data->num_phil - 1]).fork_r = &(data->forks[0]);
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
	(data->philos[ind]).write_m = &(data->mutex_write);
}

void	initialize_threads(t_philo_d *data)
{
	int	index;

	index = 0;
	pthread_mutex_init(&(data->mutex_write), NULL);
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
		index += 2;
	}
	index = 1;
	usleep(REF_RATE);
	while (index < data->num_phil)
	{
		pthread_create(&(data->threads[index]), NULL, life_cycle,
			(void *)&(data->philos[index]));
		index += 2;
	}
}
