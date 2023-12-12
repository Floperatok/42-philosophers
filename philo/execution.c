/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:56:46 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/12 17:08:34 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_the_end(t_philo *philos, t_data *data)
{
	int	i;
	int	all_eat_enough;

	while (1)
	{
		all_eat_enough = 1;
		i = -1;
		while (++i < data->number_of_philo)
		{
			if (data->times_must_eat != -1 && \
				philos[i].eaten < data->times_must_eat)
				all_eat_enough = 0;
			if (get_time_since(philos[i].time_last_meal) > data->time_to_die)
			{
				printf("%lld %d died \n", get_time_since(data->start_time), \
					i + 1);
					exit(EXIT_SUCCESS); // delete
			}
		}
		if (all_eat_enough && data->times_must_eat != -1)
			exit(EXIT_SUCCESS); // delete
	}
}

static void	*routine(void *arg)
{
	int	left_fork;
	int	right_fork;
	t_philo	*philo;

	philo = (t_philo *)arg;
	left_fork = philo->id - 1 - 1;
	right_fork = philo->id - 1;
	if (left_fork < 0)
		left_fork = philo->data->number_of_philo - 1;
	while (1)
	{
		pthread_mutex_lock(&(philo->data->forks[left_fork]));
		printf("%lld %d has taken a fork\n", get_time_since(philo->data->start_time), \
				philo->id);
		pthread_mutex_lock(&(philo->data->forks[right_fork]));
		printf("%lld %d has taken a fork\n", get_time_since(philo->data->start_time), \
				philo->id);
		printf("%lld %d is eating\n", get_time_since(philo->data->start_time), \
				philo->id);
		philo->eaten++;
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(&(philo->data->forks[left_fork]));
		pthread_mutex_unlock(&(philo->data->forks[right_fork]));
		philo->time_last_meal = get_time();
		printf("%lld %d is sleeping\n", get_time_since(philo->data->start_time), \
				philo->id);
		usleep(philo->data->time_to_sleep * 1000);
		printf("%lld %d is thinking\n", get_time_since(philo->data->start_time), \
				philo->id);
	}
	return (NULL);
}

int launch_threads(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!philos)
		return (1);
	i = -1;
	while (++i < data->number_of_philo)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].eaten = 0;
		philos[i].time_last_meal = get_time();
		if (pthread_create(&(philos[i].thread), NULL, &routine, &(philos[i])))
		{
			ft_putstr_fd("Error: Creating thread failed\n.", 2);
			return (1);
		}
		usleep(10);
	}
	wait_the_end(philos, data);		
	return (1);
}
