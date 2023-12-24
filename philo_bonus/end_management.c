/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:39:32 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/24 08:35:05 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_hunger(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->is_running)
	{

		if (get_time_since(philo->time_last_meal) > philo->data->time_to_die)
		{
			philo->is_running = 0;
			sem_post(philo->data->overall_running);
			usleep(100);
			printf("%lld\t%d %s\n", get_time_since(philo->data->start_time), \
				philo->id, "died");
			return (NULL);
		}
	}
	return (NULL);
}

void	*check_others(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->data->overall_running);
	philo->is_running = 0;
	sem_post(philo->data->overall_running);
	return (NULL);
}

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
