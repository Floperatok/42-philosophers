/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:56:46 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/14 17:57:25 by nsalles          ###   ########.fr       */
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
			pthread_mutex_lock(&(philos[i].eaten_mutex));
			if (data->times_must_eat != -1 && \
				philos[i].eaten < data->times_must_eat)
				all_eat_enough = 0;
			pthread_mutex_unlock(&(philos[i].eaten_mutex));
			pthread_mutex_lock(&(philos[i].time_last_meal_mutex));
			if (get_time_since(philos[i].time_last_meal) > data->time_to_die)
			{
				pthread_mutex_lock(&(data->start_time_mutex));
				printf("%lld\t%d died \n", get_time_since(data->start_time), \
					i + 1);
				pthread_mutex_unlock(&(data->start_time_mutex));
				{
					pthread_mutex_unlock(&(philos[i].time_last_meal_mutex));
					return ;
				}
			}
			pthread_mutex_unlock(&(philos[i].time_last_meal_mutex));
		}
		if (all_eat_enough && data->times_must_eat != -1)
			return ;
	}
}

static void	*routine(void *arg)
{
	int	left_fork;
	int	right_fork;
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(30000);
	left_fork = philo->id - 1 - 1;
	right_fork = philo->id - 1;
	if (left_fork < 0)
		left_fork = philo->data->number_of_philo - 1;
	while (1)
	{
		ft_take_fork(philo, left_fork);
		ft_take_fork(philo, right_fork);
		ft_eat(philo);
		ft_sleep(philo, left_fork, right_fork);
		ft_think(philo);
		pthread_mutex_lock(&(philo->data->is_running_mutex));
		if (!philo->data->is_running)
			break ;
		pthread_mutex_unlock(&(philo->data->is_running_mutex));
	}
	pthread_mutex_unlock(&(philo->data->is_running_mutex));
	pthread_exit(NULL);
}

int launch_threads(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!philos)
		return (1);
	data->is_running = 1;
	i = -1;
	while (++i < data->number_of_philo)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].eaten = 0;
		philos[i].time_last_meal = get_time();
		pthread_mutex_init(&(philos[i].eaten_mutex), NULL);
		pthread_mutex_init(&(philos[i].time_last_meal_mutex), NULL);
		if (pthread_create(&(philos[i].thread), NULL, &routine, &(philos[i])))
		{
			ft_putstr_fd("Error: Creating thread failed\n.", 2);
			return (1);
		}
		usleep(20);
	}
	wait_the_end(philos, data);
	pthread_mutex_lock(&(data->is_running_mutex));
	data->is_running = 0;
	pthread_mutex_unlock(&(data->is_running_mutex));
	while (--i >= 0)
	{
		if (pthread_join(philos[i].thread, NULL))
		{
			ft_putstr_fd("Error: Waiting for thread end failed\n.", 2);
			return (1);
		}
		pthread_mutex_destroy(&(philos[i].eaten_mutex));
		pthread_mutex_destroy(&(philos[i].time_last_meal_mutex));
	}
	free(philos);
	return (0);
}
