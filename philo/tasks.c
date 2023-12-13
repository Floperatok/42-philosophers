/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:35:06 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/13 21:49:15 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *philo, int fork_id)
{
	pthread_mutex_lock(&(philo->data->forks[fork_id]));
	printf("%lld %d has taken a fork\n", get_time_since(philo->data->start_time), \
				philo->id);
}

void	ft_eat(t_philo *philo, int left_fork_id, int right_fork_id)
{
	printf("%lld %d is eating\n", get_time_since(philo->data->start_time), \
				philo->id);
	philo->eaten++;
	philo->time_last_meal = get_time();
	ft_wait(philo->data->time_to_eat, &(philo->data->is_running));
	pthread_mutex_unlock(&(philo->data->forks[left_fork_id]));
	pthread_mutex_unlock(&(philo->data->forks[right_fork_id]));
}

void	ft_sleep(t_philo *philo)
{
	printf("%lld %d is sleeping\n", get_time_since(philo->data->start_time), \
			philo->id);
	ft_wait(philo->data->time_to_sleep, &(philo->data->is_running));
}

void	ft_think(t_philo *philo)
{
	printf("%lld %d is thinking\n", get_time_since(philo->data->start_time), \
				philo->id);
}