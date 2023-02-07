/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:04:35 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/02/07 18:52:02 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(void)
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
	long int	last_meal;

	if (check_dead())
		return (0);
	last_meal = get_time() - philos->last_meal;
	if (last_meal >= philos->data->time_die)
	{
		pthread_mutex_lock(&dead_call()->killer);
		dead_call()->is_dead++;
		if (dead_call()->is_dead == 1)
			print_message(philos, "died");
		pthread_mutex_unlock(&dead_call()->killer);
		return (0);
	}
	return (1);
}
