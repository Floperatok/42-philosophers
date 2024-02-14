/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:39:40 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/14 14:59:47 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	Create all the semaphores, assign them in data.
*/
void	init_semaphores(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("ate_enough");
	sem_unlink("overall_running");
	sem_unlink("is_running_sem");
	sem_unlink("is_eating");
	sem_unlink("is_printing");
	data->forks = sem_open("forks", O_CREAT, \
							S_IRUSR | S_IWUSR, data->number_of_philo);
	data->overall_running = sem_open("overall_running", O_CREAT, \
							S_IRUSR | S_IWUSR, 0);
	data->ate_enough = sem_open("ate_enough", O_CREAT, \
							S_IRUSR | S_IWUSR, 0);
	data->is_running_sem = sem_open("is_running_sem", O_CREAT, \
							S_IRUSR | S_IWUSR, 1);
	data->is_eating = sem_open("is_eating", O_CREAT, \
							S_IRUSR | S_IWUSR, 1);
	data->is_printing = sem_open("is_printing", O_CREAT, \
							S_IRUSR | S_IWUSR, 1);
}

/*
 *	Format the user arguments and assign them in data.
*/
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
	init_semaphores(data);
	data->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
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
	philo->is_running = 1;
}

/*
 *	Closes all semaphores.
*/
void	close_semaphores(t_data *data)
{
	sem_close(data->overall_running);
	sem_close(data->ate_enough);
	sem_close(data->forks);
	sem_close(data->is_running_sem);
	sem_close(data->is_eating);
	sem_close(data->is_printing);
}
