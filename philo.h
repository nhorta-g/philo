/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhorta-g <nhorta-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:24:01 by nuno              #+#    #+#             */
/*   Updated: 2023/02/17 17:32:16 by nhorta-g         ###   ########.fr       */
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
	int				on_hand;		//If available on the table slot is = 1
	pthread_mutex_t	mutex_fork;
}					t_fork;

typedef struct s_philo
{
	int				philo_id;		//Id for each philo, ranging from 1 to num_philos
	int				num_eaten;		//number times philo ate already
	int				total_forks;	//Number of forks each philo has in hands, from 1 to 2
	int				has_eaten;		//If philo has eaten > 0, iniciated at 0
	int				left_fork;
	int				right_fork;
	long int		last_meal;		//Time last meal started
	pthread_t		philo_thread;
}					t_philo;

typedef struct s_data
{
	int				num_philos;		//input from user, total philosophers
	int				time_die;		//input from user, time to die
	int				time_eat;		//input from user, time to eat
	int				time_sleep;		//input from user, time to sleep
	int				num_must_eat;	//input from user for number of times a philosopher must eat
	long int		start_time;		//t0, inicial time simulation starts
	pthread_mutex_t	mutex_print;
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
int			any_death_already(void);
int			philo_alive(t_philo *philos);

#endif
