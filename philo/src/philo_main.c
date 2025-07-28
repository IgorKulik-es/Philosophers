/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 11:29:21 by ikulik            #+#    #+#             */
/*   Updated: 2025/07/28 15:15:08 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_philo_d	data;

	if (read_values(&data, argc, argv) != 0)
		return (print_error("philo: argument error"));
	if (initialize_metadata(&data))
		return (print_error("philo: malloc or semaphore error"));
	initialize_threads(&data);
	monitor(&data);
	join_destroy(&data);
	clean_all(&data, 0);
	return (0);
}
