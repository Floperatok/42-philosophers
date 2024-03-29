/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:13:44 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/14 15:00:15 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	Only one philo routine (special case).
*/
void	one_philo_process(t_data *data)
{
	printf("0\t1 has taken a fork\n");
	usleep(data->time_to_die * 1000);
	printf("%lld\t1 died\n", get_time_since(data->start_time));
	close_semaphores(data);
	free(data);
	exit(EXIT_SUCCESS);
}

/*
 *	Only one philo creation (special case).
*/
void	one_philo(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error: Creating fork failed\n.", 2);
		return ;
	}
	if (pid == 0)
		one_philo_process(data);
	waitpid(pid, NULL, 0);
	close_semaphores(data);
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
	init_data(data, ac, av);
	if (data->times_must_eat == 0)
	{
		free(data);
		return (1);
	}
	if (data->number_of_philo == 1)
		one_philo(data);
	else if (launch_processes(data))
		return_value = 1;
	free(data);
	return (return_value);
}
