/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:39:40 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/14 13:25:28 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	Format the user arguments and assign them in data.
*/
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

/*
 *	Create all the mutexes, assign them in data.
*/
void	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&(data->start_time_mutex), NULL);
	pthread_mutex_init(&(data->is_running_mutex), NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (!data->forks)
		return ;
	i = -1;
	while (++i < data->number_of_philo)
		pthread_mutex_init(&(data->forks[i]), NULL);
	return ;
}

/*
 *	Init the values for a philo.
*/
void	init_philo(t_philo *philo, int id, t_data *data)
{
	philo->data = data;
	philo->id = id;
	philo->eaten = 0;
	philo->time_last_meal = get_time();
	pthread_mutex_init(&(philo->eaten_mutex), NULL);
	pthread_mutex_init(&(philo->time_last_meal_mutex), NULL);
}
