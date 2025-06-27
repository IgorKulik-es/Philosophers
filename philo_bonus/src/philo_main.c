/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:29:21 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/27 17:56:22 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_philo_d	data;

	if (read_values(&data, argc, argv) != 0)
	{
		write(2, "Argument error\n", 15);
		return (EXIT_FAILURE);
	}
	if (initialize_metadata(&data))
	{
		write(2, "Malloc error\n", 12);
		return (EXIT_FAILURE);
	}
	initialize_threads(&data);
	monitor(&data);
	join_destroy(&data);
	clean_all(&data, 0);
	return (0);
}
