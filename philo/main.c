/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:13:44 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/14 20:27:13 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo_thread(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	pthread_mutex_lock(&(data->forks[0]));
	printf("0\t1 has taken a fork\n");
	usleep(data->time_to_die * 1000);
	printf("%lld\t1 died\n", get_time_since(data->start_time));
	pthread_mutex_unlock(&(data->forks[0]));
	return (NULL);
}

void	one_philo(t_data *data)
{
	pthread_t	philo;

	if (pthread_create(&(philo), NULL, &one_philo_thread, data))
	{
		ft_putstr_fd("Error: Creating thread failed\n.", 2);
		return ;
	}
	if (pthread_join(philo, NULL))
	{
		ft_putstr_fd("Error: Waiting for thread end failed\n.", 2);
		return ;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		return_value;

	return_value = 0;
	if (check_errors(ac, av))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	get_infos(data, ac, av);
	if (data->times_must_eat == 0)
	{
		free(data);
		return (1);
	}
	init_mutexes(data);
	if (data->number_of_philo == 1)
		one_philo(data);
	else if (launch_threads(data))
		return_value = 1;
	destroy_mutexes(data);
	free(data->forks);
	free(data);
	return (return_value);
}
