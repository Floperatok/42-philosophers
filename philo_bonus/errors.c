/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:55:04 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/11 21:54:34 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 *	Checks if the given string has only digit character inside of it.
 *	Returns 1 if that's the case, 0 otherwise. 
*/
static int	is_all_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if ((str[i] < '0' || str[i] > '9') && str[i] != '-')
			return (0);
	return (1);
}

int	check_errors(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
	{
		printf("usage: ./philo [number_of_philosophers] [time_to_die]\
 [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]\n\
last argument is obtional and is set by default to infinity.\n");
		return (1);
	}
	i = 0;
	while (++i < ac)
	{
		if (!is_all_digit(av[i]))
		{
			ft_putstr_fd("Error: Arguments must all be numbers.\n", 2);
			return (1);
		}
		if (ft_strchr(av[i], '-'))
		{
			ft_putstr_fd("Error: Arguments must all be positives.\n", 2);
			return (1);
		}
	}
	return (0);
}
