/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:29:21 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/25 15:17:04 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_philo_d	data;

	if (read_values(&data, argc, argv) != 0)
	{
		write(2, "Argument error\n", 15);
		return (1);
	}
	initialize_metadata(&data);
	printf("Num philos:%d, start time:%ld, time to die:%d\n", data.num_phil, data.start, data.life.die);
	pthread_mutex_init(&(data.forks[0]), NULL);
	pthread_mutex_init(&(data.forks[1]), NULL);
	pthread_create(&(data.threads[0]), NULL, life_cycle, (void *)&(data.philos[0]));
	pthread_create(&(data.threads[1]), NULL, life_cycle, (void *)&(data.philos[1]));
	monitor(&data);
	pthread_join(data.threads[0], NULL);
	pthread_join(data.threads[1], NULL);
	pthread_mutex_destroy(&(data.forks[0]));
	pthread_mutex_destroy(&(data.forks[1]));
	clean_all(&data, 0);
	return (0);
}
