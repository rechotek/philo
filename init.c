/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:40:11 by mrechuli          #+#    #+#             */
/*   Updated: 2024/06/24 18:57:23 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_input(t_philo *philo, char *argv[])
{
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	philo->num_of_philos = ft_atol(argv[1]);
	if (argv[5])
		philo->num_times_to_eat = ft_atol(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
					char *argv[])
{
	int	x;

	x = 0;
	while (x < ft_atol(argv[1]))
	{
		philos[x].id = x + 1;
		philos[x].eating = 0;
		philos[x].meals_eaten = 0;
		init_input(&philos[x], argv);
		philos[x].start_time = get_current_time();
		philos[x].last_meal = get_current_time();
		philos[x].write_lock = &program->write_lock;
		philos[x].dead_lock = &program->dead_lock;
		philos[x].meal_lock = &program->meal_lock;
		philos[x].dead = &program->dead_flag;
		philos[x].l_fork = &forks[x];
		if (x == 0)
			philos[x].r_fork = &forks[philos[x].num_of_philos - 1];
		else
			philos[x].r_fork = &forks[x - 1];
		x++;
	}
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	x;

	x = 0;
	while (x < philo_num)
	{
		pthread_mutex_init(&forks[x], NULL);
		x++;
	}
}

void	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}
