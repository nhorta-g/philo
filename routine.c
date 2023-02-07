/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:34:09 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/02/07 18:48:44 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (!check_corpse())
			print_message(philo, "is thinking");
	}
	return (NULL);
}
