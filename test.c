/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:30:40 by nhorta-g          #+#    #+#             */
/*   Updated: 2023/02/07 15:40:17 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test(void)
{
	int	i;

	i = -1;
	printf("start_time: %ld\n",data()->start_time);
	printf("num_philo : %d\n",data()->num_philos);
	printf("time die  : %d\n",data()->time_die);
	printf("time_eat  : %d\n",data()->time_eat);
	printf("time_sleep: %d\n\n",data()->time_sleep);
	while (++i < data()->num_philos)
	{
		printf("exist_fork : %d\n",data()->fork[i].exist_fork);
		printf("philo_id  :  %d\n",data()->philo[i].philo_id);
		printf("num_eaten :  %d\n",data()->philo[i].num_eaten);
		printf("total_forks: %d\n",data()->philo[i].total_forks);
		printf("has_eaten:   %d\n",data()->philo[i].has_eaten);
		printf("last_meal :  %ld\n",data()->philo[i].last_meal);
		printf("sleeping  :  %ld\n\n", data()->philo[i].sleeping);
	}
}
