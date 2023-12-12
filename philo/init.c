/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:39:40 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/11 22:14:01 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_infos(t_data *data, int ac, char **av)
{
	struct timeval	time;

	data->number_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->times_must_eat = ft_atoi(av[5]);
	else
		data->times_must_eat = -1;
	gettimeofday(&time, NULL);
	data->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (!data->forks)
		return (0);
	while (++i < data->number_of_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
		{
			ft_putstr_fd("Error: One mutex for the forks failed\n", 2);
			while (--i >= 0)
				pthread_mutex_destroy(&(data->forks[i]));
			free(data->forks);
			return (1);
		}
	}
	return (0);
}
