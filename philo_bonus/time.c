/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:23:01 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/15 15:13:24 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait(long long time, int *is_running)
{
	long long	start_time;

	start_time = get_time();
	while (get_time_since(start_time) < time)
	{
		if (!*is_running)
			break ;
		usleep(10);
	}
}

/*
 *	Returns posix time converted in ms.
*/
long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*
 *	Takes posix time in ms and returns (still in ms) the time that passed since
*/
long long	get_time_since(long long time)
{
	struct timeval	time_now;
	long long		time_ms;

	gettimeofday(&time_now, NULL);
	time_ms = time_now.tv_sec * 1000 + time_now.tv_usec / 1000;
	return (time_ms - time);
}
