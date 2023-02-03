/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:50:13 by nuno              #+#    #+#             */
/*   Updated: 2023/02/03 18:57:08 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	initiate_variables(void)
{
	data()->philo = malloc(sizeof(t_philo) * data()->num_philos);
	if (!data()->philo)
		return (0);
	data()->fork = malloc(sizeof(t_fork) * data()->num_philos);
	if (!data()->philo)
		return (0);
	pthread_mutex_init(&data()->mutex)
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

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (!parse_args(ac, av))
			return (0);
		initiate_variables();
	}
	else
		printf("arguments must be 4 or 5");
}
