/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:24:01 by nuno              #+#    #+#             */
/*   Updated: 2023/02/03 18:59:04 by nhorta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_death
{
	int				is_dead;
	pthread_mutex_t	mutex_death;
}					t_death;

typedef struct s_fork
{
	int				exist_fork;
	pthread_mutex_t	mutex_fork;
}					t_fork;

typedef struct s_philo
{
	int				philo_id;
	int				num_eaten;
	int				death;
	pthread_t		philo;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_must_eat;
	long int		start_time;
	t_philo			*philo;
	t_death			*death;
	t_fork			*fork;
}					t_data;

/*utils*/
long int	get_time(void);
t_data		*data(void);
int			ft_atoi(const char *str);
int			end_and_error_message(char *msg);

#endif
