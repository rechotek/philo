/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:41:00 by mrechuli          #+#    #+#             */
/*   Updated: 2024/06/24 19:08:53 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atol(char *str)
{
	unsigned long long	num;
	int					sign;
	int					x;

	num = 0;
	sign = 1;
	x = 0;
	while (str[x] && (str[x] == ' ' || str[x] == '\r' || str[x] == '\t'
			|| str[x] == '\v' || str[x] == '\f' || str[x] == '\n'))
		x++;
	if (str[x] == '-' || str[x] == '+')
	{
		if (str[x] == '-')
			sign = -1;
		x++;
	}
	while (str[x] >= '0' && str[x] <= '9')
	{
		num = (num * 10) + (str[x] - '0');
		x++;
	}
	return (sign * num);
}

int	ft_strlen(char *str)
{
	int	x;

	if (!str)
		return (0);
	x = 0;
	while (str[x])
		x++;
	return (x);
}

void	destroy_all(char *str, t_program *program, pthread_mutex_t *forks)
{
	int	x;

	x = 0;
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	while (x < program->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&forks[x]);
		x++;
	}
}

int	ft_usleep(size_t miliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < miliseconds)
		usleep(500);
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
