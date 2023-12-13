/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:56:46 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/13 22:56:06 by nsalles          ###   ########.fr       */
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
					return ;
			}
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
	left_fork = philo->id - 1 - 1;
	right_fork = philo->id - 1;
	if (left_fork < 0)
		left_fork = philo->data->number_of_philo - 1;
	while (philo->data->is_running)
	{
		ft_take_fork(philo, left_fork);
		ft_take_fork(philo, right_fork);
		ft_eat(philo, left_fork, right_fork);
		ft_sleep(philo);
		ft_think(philo);
	}
	printf("\033[31m[exit thread %d]\033[m\n", philo->id); // delete
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
		if (pthread_create(&(philos[i].thread), NULL, &routine, &(philos[i])))
		{
			ft_putstr_fd("Error: Creating thread failed\n.", 2);
			return (1);
		}
		usleep(20);
	}
	wait_the_end(philos, data);
	data->is_running = 0;
	while (--i >= 0)
	{
		if (pthread_join(philos[i].thread, NULL))
		{
			ft_putstr_fd("Error: Waiting for thread end failed\n.", 2);
			return (1);
		}
	}
	free(philos);
	return (0);
}
