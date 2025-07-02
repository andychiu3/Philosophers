/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 08:11:05 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/07/10 09:30:07 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <string.h>
# include <unistd.h>

# define C_GRAY "\x1b[1;30m"
# define C_ORANGE "\x1b[0;33m"
# define C_RED "\x1b[0;31m"
# define C_CYAN "\x1b[0;36m"
# define NC "\x1b[0m"

# define ARG "nbr_of_philo time_to_die time_to_eat time_to_sleep [must_eat]"

typedef struct s_philo	t_philo;

typedef struct s_gnrl
{
	int				nbr_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	suseconds_t		start;
	pthread_mutex_t	monitor;
	bool			end;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}	t_gnrl;

typedef struct s_philo
{
	int				id;
	pthread_t		t_id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	suseconds_t		last_meal;
	int				meal;
	bool			eating;
	t_gnrl			*gnrl;
}	t_philo;

// utils in philo
suseconds_t	now(void);
suseconds_t	ft_msleep(suseconds_t ms);

// check
int			valid_av(int ac, char **av);
long		ft_atol(char *str);

// init
int			init_av(t_gnrl *gnrl, char **av);
int			init_fork(t_gnrl *gnrl);
int			init_philo(t_gnrl *gnrl);

// routine
void		*routine(void *arg);

// status
void		status(t_philo *philo, char *msg);
void		monitor(t_gnrl *gnrl);
void		fnd_dead(t_gnrl *gnrl);
void		eat(t_philo *philo);

#endif
