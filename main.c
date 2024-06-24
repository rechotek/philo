/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:40:20 by mrechuli          #+#    #+#             */
/*   Updated: 2024/06/24 19:01:20 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isnumber(char *arg)
{
	int	x;

	x = 0;
	while (arg[x])
	{
		if (arg[x] < '0' || arg[x] > '9')
			return (1);
		x++;
	}
	return (0);
}

int	check_valid_args(char *argv[])
{
	if ((ft_atol(argv[1]) > PHILO_MAX) || (ft_atol(argv[1]) <= 0)
		|| (ft_isnumber(argv[1]) == 1))
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atol(argv[2]) <= 0 || ft_isnumber(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atol(argv[3]) <= 0 || ft_isnumber(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atol(argv[4]) <= 0 || ft_isnumber(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atol(argv[5]) < 0 || ft_isnumber(argv[5]) == 1))
		return (write(2, "Invalid numbers of times each philosopher must eat\n",
				51), 1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_program		program;
	t_philo			philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc != 5 && argc != 6)
	{
		write(2, "Wrong argument count\n", 22);
		return (1);
	}
	if (check_valid_args(argv) == 1)
		return (1);
	init_program(&program, philos);
	init_forks(forks, ft_atol(argv[1]));
	init_philos(philos, &program, forks, argv);
	thread_create(&program, forks);
	destroy_all(NULL, &program, forks);
	return (0);
}
