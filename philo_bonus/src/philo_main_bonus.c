/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:29:21 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/28 18:29:51 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo_d	data;
	int			index;
	int			error;

	index = -1;
	if (read_values(&data, argc, argv) != 0)
	{
		write(2, "Argument error\n", 15);
		return (EXIT_FAILURE);
	}
	if (initialize_metadata_b(&data))
	{
		write(2, "Malloc or semaphore error\n", 26);
		return (EXIT_FAILURE);
	}
	while (++index < data.num_phil)
	{
		if (give_birth(&data, index) != 0)
			inject_poison(&data);
	}
	while (--index >= 0)
		waitpid(data.pids[index], &error, 0);
	clean_parent(&data, 0);
	return (0);
}
