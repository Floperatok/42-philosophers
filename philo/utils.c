/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalles <nsalles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:35:59 by nsalles           #+#    #+#             */
/*   Updated: 2023/12/13 21:24:51 by nsalles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *data)
{
	while (--data->number_of_philo)
		pthread_mutex_destroy(&(data->forks[data->number_of_philo]));
}

/*
 *	Calculates the length of the string pointed to by s, excluding the
 *	terminating null byte '\0'.
 * 	ARGUMENTS:
 * 		const char *s	: The string to calcultate the length from.
 * 	RETURN VALUE:
 * 		size_t	: Number of byte in the string pointed to by s as a size_t.
*/
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/*
 *	Writes the string s to the file descriptor fd.
 *	ARGUMENTS:
 * 		char *s	: The string to write.
 * 		int fd	: The file descriptor.
 *	RETURN VALUE:
 *		void	: None.
*/
void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

/*
 *	Search the byte c in the string s and returns a pointer to the first
 *	occurrence found.
 *	ARGUMENTS:
 * 		const char *s	: The string.
 * 		int c			: The byte to search.
 * 	RETURN VALUE:
 * 		char *	: Pointer to the matched character or NULL if the character 
 * 		is not found. 
 * 		Note that the terminating null byte is considered part or the string, 
 * 		so that if c is specified as '\0', this function return a pointer to 
 * 		the terminator.
*/
char	*ft_strchr(const char *s, int c)
{
	char	*src;

	src = (char *) s;
	while (*src != (unsigned char) c)
	{
		if (*src == '\0')
			return (NULL);
		src++;
	}
	return (src);
}

/*
 *	Convert the initial portion of the string pointed to by nptr to int.
 *	Return the converted value as an integer or 0 on error.
 *	No overflow or underflow are done. Only base-10 input cat be converted.
 *	ARGUMENTS:
 *		const char *nptr	: The string to be converted.
 *	RETURN VALUE:
 *		int	: converted value or 0 on error.
*/

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((nptr[i] && (nptr[i] >= 9 && nptr[i] <= 13)) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

void	ft_wait(long long time, int *is_running)
{
	long long	start_time;

	start_time = get_time();
	while (*is_running && get_time_since(start_time) < time)
		usleep(10);
}

/*
 *	Returns posix time converted in ms.
*/
long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*
 *	Takes posix time in ms and returns (still in ms) the time that passed since
*/
long long	get_time_since(long long time)
{
	struct timeval	time_now;
	long long		time_ms;

	gettimeofday(&time_now, NULL);
	time_ms = time_now.tv_sec * 1000 + time_now.tv_usec / 1000;
	return (time_ms - time);
}
