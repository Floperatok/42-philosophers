/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:56:46 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/24 17:00:11 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	routine(t_philo	*philo)
{
	pthread_t	hunger;
	pthread_t	others;

	pthread_create(&hunger, NULL, &check_hunger, philo); // check error
	pthread_create(&others, NULL, &check_others, philo); // check error
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 500);
	while (philo->is_running)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_sleep(philo);
		print_status("is thinking", philo);
		usleep(50);
	}
	pthread_join(hunger, NULL); // check error
	pthread_join(others, NULL); // check error
	free_data(philo->data);
	free(philo);
	exit(EXIT_SUCCESS);
}

int	launch_processes(t_data *data)
{
	int			i;
	int			*pids;
	t_philo		*philo;
	pthread_t	ate_enough;

	pids = malloc(sizeof(int) * data->number_of_philo);
	if (data->times_must_eat != -1)
		pthread_create(&ate_enough, NULL, &check_ate_enough, data); // check error
	i = -1;
	while (++i < data->number_of_philo)
	{
		philo = malloc(sizeof(t_philo)); // check error
		init_philo(philo, i + 1, data);
		pids[i] = fork();
		if (pids[i] == -1)
		{
			ft_putstr_fd("Error: Creating fork failed\n.", 2);
			return (1);
		}
		if (pids[i] == 0)
		{
			free(pids);
			routine(philo);
		}
		free(philo);
		usleep(20);
	}
	while (--i >= 0)
		waitpid(pids[i], NULL, 0);
	if (data->times_must_eat != -1)
	{
		while (++i < data->number_of_philo	)
			sem_post(data->ate_enough);
		pthread_join(ate_enough, NULL);
	}
	free(pids);
	sem_close(data->forks);
	sem_unlink("forks");
	sem_close(data->overall_running);
	sem_unlink("overall_running");
	sem_close(data->ate_enough);
	sem_unlink("ate_enough");
	return (0);
}
