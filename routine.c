/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:34:09 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/02/16 20:01:50 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_sleep(t_philo *philo)
{
	long int	sleep_time;
	long int	sleeping;

	sleep_time = get_time();
	sleeping = 0;
	if (check_dead())
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
	long int	eating_time;

	philo->last_meal = get_time();
	eating_time = 0;
	if (check_dead())
		return (0);
	if (philo_alive(philo))
	{
		print_message(philo, "is eating");
		while (eating_time <= data()->time_eat && philo_alive(philo))
			eating_time = get_time() - philo->last_meal;
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
	philo->right_fork = philo->philo_id + 1;
	philo->left_fork = philo->philo_id;
	if (philo->philo_id == data()->num_philos)
		philo->left_fork = 1;
	if (philo_alive(philo))
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
		if (!check_dead())
			print_message(philo, "is thinking");
		if (data()->num_philos % 2)
			usleep(2000);
	}
	return (0);
}
