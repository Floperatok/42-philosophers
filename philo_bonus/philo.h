/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 22:50:11 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/20 18:26:07 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pthread.h>
# include <signal.h>
# include <semaphore.h>

typedef struct s_data
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	long long int	start_time;
	sem_t			*overall_running;
	sem_t			*forks;
}		t_data;

typedef struct s_philo
{
	int				id;
	int				eaten;
	long long int	time_last_meal;
	int				is_running;
	sem_t			*eating;
	t_data			*data;
}		t_philo;

void		print_status(char *status, t_philo *philo);
void		ft_take_forks(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);

int			launch_processes(t_data *data);
void		init_philo(t_philo *philo, int id, t_data *data);
void		init_data(t_data *data, int ac, char **av);
int			check_errors(int ac, char **av);

char		*ft_strchr(const char *s, int c);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *nptr);

void		ft_wait(long long time, int *is_running);
long long	get_time(void);
long long	get_time_since(long long start_time);

#endif