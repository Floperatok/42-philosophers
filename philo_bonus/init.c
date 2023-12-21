/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:39:40 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/20 18:26:54 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, int ac, char **av)
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
	sem_unlink("forks");
	data->forks = sem_open("forks", O_CREAT, S_IRUSR | S_IWUSR, \
							data->number_of_philo);
	sem_unlink("overall_running");
	data->overall_running = sem_open("overall_running", O_CREAT, \
							S_IRUSR | S_IWUSR, 0);
	data->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
}

void	init_philo(t_philo *philo, int id, t_data *data)
{
	philo->data = data;
	philo->id = id;
	philo->eaten = 0;
	philo->time_last_meal = get_time();
	philo->is_running = 1;
	sem_unlink("eating");
	philo->eating = sem_open("eating", O_CREAT, S_IRUSR | S_IWUSR, 1);
}
