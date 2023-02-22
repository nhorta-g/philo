/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:50:13 by nuno              #+#    #+#             */
/*   Updated: 2023/02/22 09:08:57 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	initiate_variables_second(void)
{
	int	i;

	i = -1;
	data()->start_time = get_time();
	while (++i < data()->num_philos)
		pthread_create(&data()->philo[i].philo_thread, NULL, \
		&routine, &data()->philo[i]);
	while (--i > -1)
		pthread_join(data()->philo[i].philo_thread, NULL);
	return ;
}

static void	initiate_variables_first(void)
{
	int	i;

	i = -1;
	data()->philo = malloc(sizeof(t_philo) * data()->num_philos);
	if (!data()->philo)
		return ;
	data()->fork = malloc(sizeof(t_fork) * data()->num_philos);
	if (!data()->philo)
		return ;
	pthread_mutex_init(&data()->mutex_print, NULL);
	pthread_mutex_init(&data_death()->mutex_death, NULL);
	while (++i < data()->num_philos)
	{
		pthread_mutex_init(&data()->fork[i].mutex_fork, NULL);
		data()->philo[i].philo_id = i + 1;
		data()->philo[i].num_eaten = 0;
		data()->philo[i].last_meal = 0;
		data()->fork[i].on_hand = 0;
	}
	initiate_variables_second();
}

static int	parse_args(int ac, char **av)
{
	data()->num_philos = ft_atoi(av[1]);
	data()->time_die = ft_atoi(av[2]);
	data()->time_eat = ft_atoi(av[3]);
	data()->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data()->num_must_eat = ft_atoi(av[5]);
		if (data()->num_must_eat <= 0)
		{
			printf("Number of times a philosopher \
				must eat has to be greater than zero.");
			return (0);
		}
	}
	else
		data()->num_must_eat = -1;
	if (data()->num_philos <= 0 || data()->time_die <= 0 \
		|| data()->time_eat <= 0 || data()->time_sleep <= 0)
	{
		printf("Arguments must greater than zero.");
		return (0);
	}
	return (1);
}

void	exit_program(void)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data()->mutex_print);
	pthread_mutex_destroy(&data_death()->mutex_death);
	while (++i < data()->num_philos)
		pthread_mutex_destroy(&data()->fork[i].mutex_fork);
	if (data()->fork)
		free(data()->fork);
	if (data()->philo)
		free(data()->philo);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (!parse_args(ac, av))
			return (0);
		initiate_variables_first();
		exit_program();
	}
	else
		printf("arguments must be 4 or 5");
}
