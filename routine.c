/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:34:09 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/02/08 16:12:25 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_nap(t_philo *philo)
{
	long int	nap_time;
	long int	sleeping;

	nap_time = get_time();
	sleeping = 0;
	if (check_dead())
		return (0);
	print_message(philo, "is sleeping");
	usleep(100);
	while (sleeping <= data()->time_sleep)
		sleeping = get_time() - nap_time;
	return (1);
}

static int	available_forks(t_philo *philo, int index)
{
	while (philo_alive(philo))
	{
		pthread_mutex_lock(&data()->fork[index].mutex_fork);
		if (data()->fork[index].exist_fork == 0)
		{
			data()->fork[index].exist_fork = 1;
			philo->total_forks++;
			print_message(philo, "has taken a fork");
			pthread_mutex_unlock(&data()->fork[index].mutex_fork);
			return (1);
		}
		if (philo->has_eaten > 0 && data()->fork[index].exist_fork == 1)
		{
			data()->fork[index].exist_fork = 0;
			philo->has_eaten--;
			pthread_mutex_unlock(&data()->fork[index].mutex_fork);
			return (0);
		}
		pthread_mutex_unlock(&data()->fork[index].mutex_fork);
	}
	return (1);
}

static int	philo_eat(t_philo *philo)
{
	long int	eat_time;
	long int	eating;

	eat_time = get_time();
	eating = 0;
	if (check_dead())
		return (0);
	usleep(100);
	if (philo_alive(philo))
	{
		print_message(philo, "is eating");
		while (eating <= data()->time_eat && philo_alive(philo))
			eating = get_time() - eat_time;
		philo->last_meal = get_time();
		philo->has_eaten = 2;
		available_forks(philo, philo->right_fork);
		available_forks(philo, philo->left_fork);
		philo->total_forks = 0;
		philo->num_eaten++;
	}
	return (1);
}

static int	check_forks(t_philo *philo)
{
	int	left;
	int	right;

	right = philo->philo_id;
	left = philo->philo_id + 1;
	if (philo->philo_id == data()->num_philos)
		left = 1;
	philo->right_fork = right;
	philo->left_fork = left;
	while (philo_alive(philo))
	{
		available_forks(philo, right);
		available_forks(philo, left);
		if (philo->total_forks == 2)
			philo_eat(philo);
		return (1);
	}
	return (0);
}

void	*routine(void *t)
{
	t_philo	*philo;

	philo = (t_philo *)t;
	philo->last_meal = data()->start_time;
	while (philo_alive(philo))
	{
		check_forks(philo);
		if (philo->num_eaten == data()->num_must_eat)
			return (NULL);
		philo_nap(philo);
		usleep(100);
		if (!check_dead())
			print_message(philo, "is thinking");
	}
	return (NULL);
}
