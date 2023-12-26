/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:35:06 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/25 11:51:22 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(char *status, t_philo *philo)
{
	sem_wait(philo->data->is_running_sem);
	if (philo->is_running || ft_strncmp(status, "died", 4) == 0)
	{
		sem_post(philo->data->is_running_sem);
		sem_wait(philo->data->is_printing);
		printf("%lld\t%d %s\n", get_time_since(philo->data->start_time), \
			philo->id, status);
		sem_post(philo->data->is_printing);
		return ;
	}
	sem_post(philo->data->is_running_sem);
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
	sem_wait(philo->data->is_eating);
	philo->eaten++;
	philo->time_last_meal = get_time();
	if (philo->data->times_must_eat != -1 && \
		philo->eaten == philo->data->times_must_eat)
		sem_post(philo->data->ate_enough);
	sem_post(philo->data->is_eating);
	print_status("is eating", philo);
	ft_wait(philo->data->time_to_eat, &(philo->is_running), philo->data->is_running_sem);
}

void	ft_sleep(t_philo *philo)
{
	print_status("is sleeping", philo);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	ft_wait(philo->data->time_to_sleep, &(philo->is_running), philo->data->is_running_sem);
}
