/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:56:46 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/26 19:43:20 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	routine(t_philo	*philo)
{
	pthread_t	hunger;
	pthread_t	others;

	pthread_create(&hunger, NULL, &check_hunger, philo);
	pthread_create(&others, NULL, &check_others, philo);
	if (philo->id % 2 == 0)
		usleep(15000);
	while (1)
	{
		sem_wait(philo->data->is_running_sem);
		if (!philo->is_running)
			break ;
		sem_post(philo->data->is_running_sem);
		tasks(philo);
		usleep(50);
	}
	sem_post(philo->data->is_running_sem);
	pthread_join(hunger, NULL);
	pthread_join(others, NULL);
	close_semaphores(philo->data);
	free(philo->data);
	free(philo);
	exit(EXIT_SUCCESS);
}

int	wait_processes(t_data *data, int *pids, pthread_t ate_enough)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philo)
		waitpid(pids[i], NULL, 0);
	if (data->times_must_eat != -1)
	{
		while (--i >= 0)
			sem_post(data->ate_enough);
		pthread_join(ate_enough, NULL);
	}
	free(pids);
	close_semaphores(data);
	return (0);
}

int	launch_processes(t_data *data)
{
	int			i;
	int			*pids;
	t_philo		*philo;
	pthread_t	ate_enough;

	pids = malloc(sizeof(int) * data->number_of_philo);
	if (data->times_must_eat != -1)
		pthread_create(&ate_enough, NULL, &check_ate_enough, data);
	i = -1;
	while (++i < data->number_of_philo)
	{
		philo = malloc(sizeof(t_philo));
		init_philo(philo, i + 1, data);
		pids[i] = fork();
		if (pids[i] == -1)
			return (ft_putstr_fd("Error: Creating fork failed\n.", 2), 1);
		if (pids[i] == 0)
		{
			free(pids);
			routine(philo);
		}
		free(philo);
	}
	wait_processes(data, pids, ate_enough);
	return (0);
}
