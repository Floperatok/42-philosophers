/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:35:06 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/24 00:38:32 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(char *status, t_philo *philo)
{
	if (philo->is_running)
	{
		printf("%lld\t%d %s\n", get_time_since(philo->data->start_time), \
			philo->id, status);
	}
}

void	ft_take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_status("has taken a fork", philo);
	sem_wait(philo->data->forks);
	print_status("has taken a fork", philo);
}

void	ft_eat(t_philo *philo)
{
	print_status("is eating", philo);
	philo->eaten++;
	philo->time_last_meal = get_time();
	if (philo->data->times_must_eat != -1 && \
		philo->eaten == philo->data->times_must_eat)
		sem_post(philo->data->ate_enough);
	ft_wait(philo->data->time_to_eat, &(philo->is_running));
}

void	ft_sleep(t_philo *philo)
{
	print_status("is sleeping", philo);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	ft_wait(philo->data->time_to_sleep, &(philo->is_running));
}
