/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:40:34 by mrechuli          #+#    #+#             */
/*   Updated: 2024/06/24 19:02:59 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - philo->start_time;
	if (!dead_loop(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

int	philo_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if ((get_current_time() - philo->last_meal >= time_to_die)
		&& philo->eating == 0)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_if_any_dead(t_philo *philos)
{
	int	x;

	x = 0;
	while (x < philos[0].num_of_philos)
	{
		if (philo_dead(&philos[x], philos[x].time_to_die))
		{
			print_message("died", &philos[x], philos[x].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		x++;
	}
	return (0);
}

int	check_if_all_ate(t_philo *philos)
{
	int	x;
	int	finished_eating;

	x = 0;
	finished_eating = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (x < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[x].meal_lock);
		if (philos[x].meals_eaten >= philos[x].num_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[x].meal_lock);
		x++;
	}
	if (finished_eating == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (check_if_any_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
	}
	return (pointer);
}
