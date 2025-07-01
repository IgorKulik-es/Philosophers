/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:29:21 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/30 15:35:43 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo_d	data;
	int			error_code;

	error_code = 0;
	if (read_values(&data, argc, argv) != 0)
		return (print_error("philo: argument error"));
	if (initialize_metadata_b(&data))
		return (print_error("philo: malloc or semaphore error"));
	if (give_birth(&data) != 0)
	{
		sem_fill(&data, data.sem_stop);
		print_error("philo: fork error");
		error_code = EXIT_FAILURE;
	}
	wait_sems_pids(&data);
	clean_parent(&data, 0);
	return (error_code);
}
