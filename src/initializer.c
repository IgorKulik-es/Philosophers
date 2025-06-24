/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:47:48 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/24 20:19:01 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	data->life.food = INT_MAX;
	if (argc == 6)
		data->life.food = ft_atoi(argv[5]);
	return (0);
}

int	initialize_metadata(t_philo_d *data)
{
	int	index;

	index = -1;
	data->threads = (pthread_t *)malloc(data->num_phil * sizeof(pthread_t));
	data->forks = (pthread_mutex_t *)malloc(data->num_phil
			* sizeof(pthread_mutex_t));
	data->philos = (t_guy *)malloc(data->num_phil * sizeof(t_guy));
	if (data->forks == NULL || data->philos == NULL || data->philos == NULL)
		return (clean_all(data, EXIT_FAILURE));
	data->start = c_time();
	while (++index < data->num_phil)
		initialize_philo(data, index);
	(data->philos[data->num_phil - 1]).right_f = &(data->forks[0]);
	return (0);
}

void	initialize_philo(t_philo_d *data, int ind)
{
	(data->philos[ind]).start = data->start;
	(data->philos[ind]).eat_t = data->start;
	(data->philos[ind]).die_t = data->start + data->life.die;
	(data->philos[ind]).sleep_t = data->start + data->life.sleep;
	(data->philos[ind]).left_f = &(data->forks[ind]);
	if (ind < data->num_phil - 1)
		(data->philos[ind]).right_f = &(data->forks[ind + 1]);
	(data->philos[ind]).state = THINK;
	if ((ind % 2) == 1 && !(((ind % 2) == 1) && ind == data->num_phil))
		(data->philos[ind]).state = SLEEP;
	(data->philos[ind]).meals_had = 0;
	(data->philos[ind]).index = ind;
	(data->philos[ind]).life = &(data->life);
}
