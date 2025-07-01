/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:51:31 by ikulik            #+#    #+#             */
/*   Updated: 2025/06/28 18:10:25 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	is_positive;

	result = 0;
	is_positive = 1;
	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			is_positive = -1;
		nptr++;
	}
	while ('0' <= *nptr && *nptr <= '9')
	{
		result = result * 10 + *nptr - '0';
		nptr++;
	}
	result *= is_positive;
	return (result);
}

time_t	c_time(void)
{
	struct timeval	time_current;

	gettimeofday(&time_current, NULL);
	return (time_current.tv_sec * 1000 + time_current.tv_usec / 1000);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
