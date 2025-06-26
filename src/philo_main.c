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
	initialize_threads(&data);
	monitor(&data);
	join_destroy(&data);
	clean_all(&data, 0);
	return (0);
}
