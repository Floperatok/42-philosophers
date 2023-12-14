/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 22:50:11 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/14 19:10:09 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				is_running;
	long long int	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	start_time_mutex;
	pthread_mutex_t	is_running_mutex;
}		t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eaten;
	long long int	time_last_meal;
	pthread_mutex_t	eaten_mutex;
	pthread_mutex_t	time_last_meal_mutex;
	t_data			*data;
}		t_philo;

void		print_status(char *status, t_philo *philo);
void		ft_take_forks(t_philo *philo, int left_fork, int right_fork);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo, int left_fork_id, int right_fork_id);
void		ft_think(t_philo *philo);

int			launch_threads(t_data *data);
void		init_mutexes(t_data *data);
void		init_philo(t_philo *philo, int id, t_data *data);
void		get_infos(t_data *data, int ac, char **av);
int			check_errors(int ac, char **av);

void		destroy_mutexes(t_data *data);
char		*ft_strchr(const char *s, int c);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *nptr);

void		ft_wait(long long time, int *is_running, pthread_mutex_t *mutex);
long long	get_time(void);
long long	get_time_since(long long start_time);

#endif