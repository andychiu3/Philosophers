/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:41:43 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/07/10 09:29:34 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	now(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

// usleep is not accurate enough
suseconds_t	ft_msleep(suseconds_t ms)
{
	suseconds_t	start;

	start = now();
	while (now() - start < ms)
		usleep(500);
	return (0);
}

// gnrl->monitor always valid
// idealy may need another bool to record if init or not?
void	exit_point(t_gnrl *gnrl)
{
	int	i;

	if (gnrl->fork)
	{
		i = -1;
		while (++i < gnrl->nbr_of_philo)
			pthread_mutex_destroy(&gnrl->fork[i]);
		free (gnrl->fork);
		gnrl->fork = NULL;
	}
	pthread_mutex_destroy(&gnrl->monitor);
	if (gnrl->philo)
	{
		free (gnrl->philo);
		gnrl->philo = NULL;
	}
}

// idealy may have to consider join if create fail
// seems that we don't need another thread to monitor
void	thread_start(t_gnrl *gnrl)
{
	int			i;

	gnrl->start = now();
	i = -1;
	while (++i < gnrl->nbr_of_philo)
		if (pthread_create(&gnrl->philo[i].t_id, NULL,
				routine, (void *)&gnrl->philo[i]))
			return ;
	monitor(gnrl);
	i = -1;
	while (++i < gnrl->nbr_of_philo)
		if (pthread_join(gnrl->philo[i].t_id, NULL))
			return ;
}

int	main(int ac, char **av)
{
	t_gnrl	gnrl;

	if (valid_av(ac, av) && init_av(&gnrl, av))
	{
		if (init_fork(&gnrl) && init_philo(&gnrl))
		{
			thread_start(&gnrl);
			exit_point(&gnrl);
		}
	}
}

/*
edge cases
1. only one philo
2. last_meal_time should be updated again at last X
3. die while taking forks -> skip the rest
4. die while eating -> use bool X
5. must_eat_time got 0
6. definition of data race????
*/