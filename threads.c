/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:40:54 by mrechuli          #+#    #+#             */
/*   Updated: 2024/06/24 19:07:20 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			x;

	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		destroy_all("Thread creation error", program, forks);
	x = 0;
	while (x < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[x].thread, NULL, &philo_routine,
				&program->philos[x]) != 0)
			destroy_all("Thread creation error", program, forks);
		x++;
	}
	x = 0;
	if (pthread_join(observer, NULL) != 0)
		destroy_all("Thread join error", program, forks);
	while (x < program->philos[0].num_of_philos)
	{
		if (pthread_join(program->philos[x].thread, NULL) != 0)
			destroy_all("Thread join error", program, forks);
		x++;
	}
	return (0);
}
