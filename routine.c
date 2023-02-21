/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:34:09 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/02/21 18:22:14 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_sleep(t_philo *philo)
{
	long int	sleep_time;
	long int	sleeping;

	sleep_time = get_time();
	sleeping = 0;
	if (any_death_already())
		return (0);
	print_message(philo, "is sleeping");
	while (sleeping <= data()->time_sleep)
		sleeping = get_time() - sleep_time;
	return (1);
}

static int	available_forks(t_philo *philo, int index)
{
	while (philo_alive(philo))
	{
		pthread_mutex_lock(&data()->fork[index].mutex_fork);
		if (data()->fork[index].on_hand == 0)
		{
			data()->fork[index].on_hand = 1;
			philo->total_forks++;
			print_message(philo, "has taken a fork");
			pthread_mutex_unlock(&data()->fork[index].mutex_fork);
			return (1);
		}
		if (philo->has_eaten > 0 && data()->fork[index].on_hand == 1)
		{
			data()->fork[index].on_hand = 0;
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
	long int	eating_duration;
	long int	start_eat_time;

	eating_duration = 0;
	start_eat_time = get_time();
	if (any_death_already())
		return (0);
	if (philo_alive(philo))
	{
		print_message(philo, "is eating");
		while (eating_duration <= data()->time_eat && philo_alive(philo))
			eating_duration = get_time() - start_eat_time;
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
	philo->right_fork = philo->philo_id;
	philo->left_fork = philo->philo_id + 1;
	if (philo->philo_id == data()->num_philos)
		philo->left_fork = 1;
	while (philo_alive(philo))
	{
		available_forks(philo, philo->right_fork);
		available_forks(philo, philo->left_fork);
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
	if (!(philo->philo_id % 2))
		usleep(10000);
	philo->last_meal = data()->start_time;
	while (philo_alive(philo))
	{
		check_forks(philo);
		if (philo->num_eaten == data()->num_must_eat)
			return (0);
		philo_sleep(philo);
		if (!any_death_already())
			print_message(philo, "is thinking");
		if (data()->num_philos % 2)
			usleep(2000);
	}
	return (0);
}
