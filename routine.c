/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:54:15 by nuno              #+#    #+#             */
/*   Updated: 2023/02/22 09:42:28 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_action(long long action, t_philo *philo)
{
	long long	begin;
	long long	passed;

	begin = get_time();
	passed = 0;
	while (philo_alive(philo) && passed < action)
	{
		if (any_death_already())
			return (1);
		usleep(100);
		passed = time_diff(begin, get_time());
	}
	return (passed >= action);
}

void	putting_forks(int fork)
{
	pthread_mutex_lock(&data()->fork[fork].mutex_fork);
	data()->fork[fork].on_hand = 0;
	pthread_mutex_unlock(&data()->fork[fork].mutex_fork);
}

void	taking_fork(t_philo *philo, int fork)
{
	while (philo_alive(philo))
	{
		pthread_mutex_lock(&data()->fork[fork].mutex_fork);
		if (!data()->fork[fork].on_hand)
		{
			data()->fork[fork].on_hand = 1;
			pthread_mutex_unlock(&data()->fork[fork].mutex_fork);
			break;
		}
		else
			pthread_mutex_unlock(&data()->fork[fork].mutex_fork);
	}
}

int	eat(t_philo *philo)
{
	int	right;
	int	left;

	right = philo->philo_id + 1;
	left = philo->philo_id;
	if (philo->philo_id == data()->num_philos)
		left = 1;
	taking_fork(philo, right);
	if (any_death_already())
		return (1);
	print_message(philo, "has taken a fork");
	taking_fork(philo, left);
	if (any_death_already())
		return (1);
	print_two_messages(philo);
	philo->num_eaten++;
	philo->last_meal = get_time() - data()->start_time;
	sleep_action(data()->time_eat, philo);
	putting_forks(right);
	putting_forks(left);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->philo_id % 2))
		usleep(10000);
	while (philo_alive(philo))
	{
		if (eat(philo))
			return (NULL);
		if ((data()->num_must_eat != -1
				&& philo->num_eaten == data()->num_must_eat) \
					|| !philo_alive(philo))
			break;
		print_message(philo, "is sleeping");
		sleep_action(data()->time_sleep, philo);
		if (!philo_alive(philo))
			return (NULL);
		print_message(philo, "is thinking");
		if (data()->num_philos % 2)
			usleep(2000);
	}
	return (NULL);
}
