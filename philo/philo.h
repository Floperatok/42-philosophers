/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 22:50:11 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/12 17:01:39 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	pthread_mutex_t	*forks;
	long long int	start_time;
}		t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eaten;
	long long int	time_last_meal;
	t_data			*data;
}		t_philo;


int			launch_threads(t_data *data);
int			init_mutexes(t_data *data);
void		get_infos(t_data *data, int ac, char **av);
int			check_errors(int ac, char **av);

void		destroy_mutexes(t_data *data);
char		*ft_strchr(const char *s, int c);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *nptr);
long long	get_time(void);
long long	get_time_since(long long start_time);

#endif