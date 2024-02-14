/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:23:01 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/14 13:35:34 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	Wait the given amount of time in millisecond. Stops if is_running becomes 0. 
*/
void	ft_wait(long long time, int *is_running, pthread_mutex_t *mutex)
{
	long long	start_time;

	start_time = get_time();
	while (get_time_since(start_time) < time)
	{
		pthread_mutex_lock(mutex);
		if (!*is_running)
		{
			pthread_mutex_unlock(mutex);
			break ;
		}
		pthread_mutex_unlock(mutex);
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
