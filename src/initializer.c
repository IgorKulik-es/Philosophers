/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:47:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/21 13:47:48 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	read_values(t_philo_d *data,int argc, char **argv)
{
	if (argc != 4 || argc != 5)
		return (1);
	data->life.num = ft_atoi(argv[1]);
	data->num_phil = data->life.num;
	data->life.eat = ft_atoi(argv[2]);
	data->life.sleep = ft_atoi(argv[3]);
	data->life.food = INT_MAX;
	if (argc == 5)
		data->life.food = ft_atoi(argv[4]);
}

int	initialize_threads(t_philo_d *data)
{
	int	index;
	
	data->threads = (pthread_t *)malloc(data->num_phil * sizeof(pthread_t));
	data->forks = (pthread_mutex_t *)malloc(data->num_phil 
		* sizeof(pthread_mutex_t));
	data->philos = (t_guy *)malloc(data->num_phil * sizeof(t_guy));
	if (data->forks == NULL || data->philos == NULL || data->philos == NULL)
		return (1);
	data->start = ft_timer();
	while (index < data->num_phil)
	{
		(data->philos[index]).l_meal = data->start;
		(data->philos[index]).left_f = data->forks[index];
		if (index < data->num_phil - 1)
			(data->philos[index]).right_f = data->forks[index + 1];
		(data->philos[index]).state = THINK;
		(data->philos[index]).meals_had = 0;
		(data->philos[index]).index = index;
		(data->philos[index]).life = &(data->life);
	}
	(data->philos[data->num_phil - 1]).right_f = data->forks[0];
}
