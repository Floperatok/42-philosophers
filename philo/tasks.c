/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:35:06 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/14 20:55:02 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(char *status, t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->is_running_mutex));
	if (philo->data->is_running)
	{
		pthread_mutex_lock(&(philo->data->start_time_mutex));
		printf("%lld\t%d %s\n", get_time_since(philo->data->start_time), \
			philo->id, status);
		pthread_mutex_unlock(&(philo->data->start_time_mutex));
	}
	pthread_mutex_unlock(&(philo->data->is_running_mutex));
}

void	ft_take_forks(t_philo *philo, int left_fork, int right_fork)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&(philo->data->forks[right_fork]));
		print_status("has taken a fork", philo);
		pthread_mutex_lock(&(philo->data->forks[left_fork]));
		print_status("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(&(philo->data->forks[left_fork]));
		print_status("has taken a fork", philo);
		pthread_mutex_lock(&(philo->data->forks[right_fork]));
		print_status("has taken a fork", philo);
	}
}

void	ft_eat(t_philo *philo)
{
	print_status("is eating", philo);
	pthread_mutex_lock(&(philo->eaten_mutex));
	philo->eaten++;
	pthread_mutex_unlock(&(philo->eaten_mutex));
	pthread_mutex_lock(&(philo->time_last_meal_mutex));
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&(philo->time_last_meal_mutex));
	ft_wait(philo->data->time_to_eat, &(philo->data->is_running), \
			&(philo->data->is_running_mutex));
}

void	ft_sleep(t_philo *philo, int left_fork_id, int right_fork_id)
{
	print_status("is sleeping", philo);
	pthread_mutex_unlock(&(philo->data->forks[left_fork_id]));
	pthread_mutex_unlock(&(philo->data->forks[right_fork_id]));
	ft_wait(philo->data->time_to_sleep, &(philo->data->is_running), \
			&(philo->data->is_running_mutex));
}

void	ft_died(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->is_running_mutex));
	data->is_running = 0;
	pthread_mutex_unlock(&(data->is_running_mutex));
	usleep(100);
	pthread_mutex_lock(&(philo->data->start_time_mutex));
	printf("%lld\t%d %s\n", get_time_since(philo->data->start_time), \
			philo->id, "died");
	pthread_mutex_unlock(&(philo->data->start_time_mutex));
	pthread_mutex_unlock(&(philo->time_last_meal_mutex));
}
