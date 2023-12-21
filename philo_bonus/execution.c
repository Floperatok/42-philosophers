/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:56:46 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/21 11:46:24 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *check_other_end(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->data->overall_running);
	philo->is_running = 0;
	sem_post(philo->data->overall_running);
	return (NULL);
}

static void	*check_self_end(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->is_running)
	{
		if (philo->data->times_must_eat != -1 && \
			philo->eaten < philo->data->times_must_eat)
		{
			philo->is_running = 0;
			return (NULL);
		}
		sem_wait(philo->eating);
		if (get_time_since(philo->time_last_meal) > philo->data->time_to_die)
		{
			philo->is_running = 0;
			usleep(100);
			printf("%lld\t%d %s\n", get_time_since(philo->data->start_time), \
				philo->id, "died");
			sem_post(philo->eating); // not within access region
			return (NULL);
		}
		sem_post(philo->eating);
	}
	return (NULL);
}

static void	routine(t_philo	*philo)
{
	pthread_t	self_thread;
	pthread_t	other_thread;

	pthread_create(&self_thread, NULL, &check_self_end, philo); // check error
	pthread_detach(self_thread);
	pthread_create(&other_thread, NULL, &check_other_end, philo); // check error
	pthread_detach(other_thread);
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (philo->is_running)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_sleep(philo);
		print_status("is thinking", philo);
	}
	sem_close(philo->eating);
	sem_unlink("eating");
	exit(EXIT_SUCCESS);
}

int	launch_processes(t_data *data)
{
	int		i;
	int		*pids;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * data->number_of_philo);
	pids = malloc(sizeof(int) * data->number_of_philo);
	if (!philos)
		return (1);
	i = -1;
	while (++i < data->number_of_philo)
	{
		init_philo(&(philos[i]), i + 1, data);
		pids[i] = fork();
		if (pids[i] == -1)
		{
			ft_putstr_fd("Error: Creating fork failed\n.", 2);
			return (1);
		}
		if (pids[i] == 0)
			routine(&(philos[i]));
		usleep(20);
	}
	while (--i >= 0)
		waitpid(pids[i], NULL, 0);
	free(pids);
	free(philos);
	sem_close(data->forks);
	sem_unlink("forks");
	sem_close(data->overall_running);
	sem_unlink("overall_running");
	return (0);
}
