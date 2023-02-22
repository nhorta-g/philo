/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuno <nuno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:24:01 by nuno              #+#    #+#             */
/*   Updated: 2023/02/22 09:36:30 by nuno             ###   ########.fr       */
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

/*
is_dead -> If at least on philosopher is dead value is >= 0;
*/

typedef struct s_fork
{
	int				on_hand;
	pthread_mutex_t	mutex_fork;
}					t_fork;

/*
on_hand -> If fork is on philosopher hand is = 1, on table 0;
*/

typedef struct s_philo
{
	int				philo_id;
	int				num_eaten;
	long int		last_meal;
	pthread_t		philo_thread;
}					t_philo;

/*
philo_id -> Id for each philosopher, ranging from 1 to num_philos;
num_eaten -> Number times philo ate already during simulation;
last_meal -> Time last meal started;
*/

typedef struct s_data
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_must_eat;
	long int		start_time;
	pthread_mutex_t	mutex_print;
	t_philo			*philo;
	t_death			*death;
	t_fork			*fork;
}					t_data;
/*
num_philos -> Input from user, total philosophers;
time_die -> Input from user, time to die;
time_eat -> Input from user, time to eat
time_sleep -> Input from user, time to sleep;
num_must_eat -> Input from user for number of times a philosopher must eat;
start_time -> t0, inicial time simulation starts;
*/

/*utils*/
t_data		*data(void);
t_death		*data_death(void);
long int	get_time(void);
long int	time_diff(long int start, long int last_action);
int			ft_atoi(const char *str);

/*routine*/
void		*routine(void *t);

/*death_print*/
int			any_death_already(void);
int			philo_alive(t_philo *philos);
void		print_message(t_philo *philo, char *str);
void		print_two_messages(t_philo *philo);

#endif
