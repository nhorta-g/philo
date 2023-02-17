/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:56:29 by nuno              #+#    #+#             */
/*   Updated: 2023/02/17 17:20:09 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

t_death	*data_death(void)
{
	static t_death	data;

	return (&data);
}

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&data()->mutex_print);
	printf("%ld %i %s		%ld\n", get_time() - \
		data()->start_time, philo->philo_id, str, \
		get_time() - philo->last_meal);
	pthread_mutex_unlock(&data()->mutex_print);
	return ;
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	num;

	i = 0;
	num = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (num > 2147483647)
			return (0);
		i++;
	}
	return (num);
}
