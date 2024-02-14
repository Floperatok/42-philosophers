/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:39:32 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/14 14:51:55 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	Continuously checks if the philo dies of starvation. Sets philo->is_running
 *	to 0 and unlock data->overall_running if he does.
*/
void	*check_hunger(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->is_running_sem);
		if (!philo->is_running)
			break ;
		sem_post(philo->data->is_running_sem);
		sem_wait(philo->data->is_eating);
		if (get_time_since(philo->time_last_meal) > philo->data->time_to_die)
		{
			sem_post(philo->data->is_eating);
			philo->is_running = 0;
			sem_post(philo->data->overall_running);
			usleep(100);
			print_status("died", philo);
			return (NULL);
		}
		sem_post(philo->data->is_eating);
	}
	sem_post(philo->data->is_running_sem);
	return (NULL);
}

/*
 *	Waits for data->overall_running to unlock, sets philo->is_running to 0
 *	when it does.
*/
void	*check_others(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->data->overall_running);
	sem_wait(philo->data->is_running_sem);
	philo->is_running = 0;
	sem_post(philo->data->is_running_sem);
	sem_post(philo->data->overall_running);
	return (NULL);
}

/*
 *	Wait until all the philos have eaten enough, then unlock 
 *	data->overall_running.
*/
void	*check_ate_enough(void *arg)
{
	int		counter;
	int		number_of_philo;
	t_data	*data;

	data = (t_data *)arg;
	number_of_philo = data->number_of_philo;
	counter = 0;
	while (counter < number_of_philo)
	{
		sem_wait(data->ate_enough);
		counter++;
	}
	sem_post(data->overall_running);
	return (NULL);
}
