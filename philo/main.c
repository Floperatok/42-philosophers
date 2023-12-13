/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:13:44 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/13 22:55:58 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
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
	if (init_mutexes(data))
	{
		free(data);
		return (1);
	}
	if (launch_threads(data))
		return_value = 1;
	destroy_mutexes(data);
	free(data->forks);
	free(data);
	return (return_value);
}
