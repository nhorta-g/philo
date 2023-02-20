/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:04:35 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/02/20 15:03:36 by nuno             ###   ########.fr       */
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
	long int	time_between_meals;

	if (any_death_already())
		return (0);
	time_between_meals = get_time() - philos->last_meal;
	if (time_between_meals >= data()->time_die)
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
