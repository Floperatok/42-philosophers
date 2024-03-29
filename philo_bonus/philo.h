/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 22:50:11 by nsalles           #+#    #+#             */
/*   Updated: 2024/02/14 14:59:46 by nsalles          ###   ########.fr       */
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
	sem_t			*ate_enough;
	sem_t			*forks;
	sem_t			*is_running_sem;
	sem_t			*is_eating;
	sem_t			*is_printing;
}		t_data;

typedef struct s_philo
{
	int				id;
	int				eaten;
	long long int	time_last_meal;
	int				is_running;
	t_data			*data;
}		t_philo;

void		print_status(char *status, t_philo *philo);
void		ft_take_forks(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		tasks(t_philo *philo);

int			launch_processes(t_data *data);
void		init_philo(t_philo *philo, int id, t_data *data);
void		init_data(t_data *data, int ac, char **av);
void		close_semaphores(t_data *data);

void		*check_hunger(void *arg);
void		*check_others(void *arg);
void		*check_ate_enough(void *arg);

char		*ft_strchr(const char *s, int c);
void		ft_putstr_fd(char *s, int fd);
int			ft_atoi(const char *nptr);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_wait(long long time, int *is_running, sem_t *sem);
long long	get_time(void);
long long	get_time_since(long long start_time);
int			check_errors(int ac, char **av);

#endif