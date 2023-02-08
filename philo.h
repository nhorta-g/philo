/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:24:01 by nuno              #+#    #+#             */
/*   Updated: 2023/02/08 17:48:35 by nuno             ###   ########.fr       */
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
	int				total_forks;
	int				has_eaten;
	int				left_fork;
	int				right_fork;
	long int		last_meal;
	long int		sleeping;
	pthread_t		philo_thread;
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
t_data		*data(void);
t_death		*data_death(void);
long int	get_time(void);
void		print_message(t_philo *philo, char *str);
int			ft_atoi(const char *str);

/*routine*/
void		*routine(void *t);

/*death*/
int			check_dead(void);
int			philo_alive(t_philo *philos);

/*test*/
void		test(void);

#endif
