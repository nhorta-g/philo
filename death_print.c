/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:04:35 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/02/22 09:18:26 by nuno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	any_death_already(void)
{
	int	dead;

	pthread_mutex_lock(&data_death()->mutex_death);
	dead = data_death()->is_dead;
	pthread_mutex_unlock(&data_death()->mutex_death);
	if (dead)
		return (1);
	return (0);
}

int	philo_alive(t_philo *philos)
{
	if (any_death_already())
		return (0);
	if (time_diff(philos->last_meal, get_time() \
		- data()->start_time) >= data()->time_die)
	{
		pthread_mutex_lock(&data_death()->mutex_death);
		data_death()->is_dead++;
		if (data_death()->is_dead == 1)
			print_message(philos, "died");
		pthread_mutex_unlock(&data_death()->mutex_death);
		return (0);
	}
	return (1);
}

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&data()->mutex_print);
	printf("%ld %i %s\n", get_time() - \
		data()->start_time, philo->philo_id, str);
	pthread_mutex_unlock(&data()->mutex_print);
	return ;
}

void	print_two_messages(t_philo *philo)
{
	pthread_mutex_lock(&data()->mutex_print);
	printf("%lu %i %s\n", \
	time_diff(data()->start_time, get_time()),
		philo->philo_id, "has taken a fork");
	printf("%lu %i %s\n", \
	time_diff(data()->start_time, get_time()), philo->philo_id, "is eating");
	pthread_mutex_unlock(&data()->mutex_print);
	philo->last_meal = get_time();
}
