/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:05:51 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/07/10 09:36:02 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fnd_dead(t_gnrl *gnrl)
{
	int	i;

	i = -1;
	while (++i < gnrl->nbr_of_philo)
	{
		if (now() - gnrl->philo[i].last_meal >= gnrl->time_to_die)
		{
			printf("\n%d %d died\n", now() - gnrl->start,
				gnrl->philo[i].id);
			gnrl->end = true;
			return ;
		}
	}
}

void	all_eaten(t_gnrl *gnrl)
{
	int	i;

	if (gnrl->must_eat < 0)
		return ;
	i = -1;
	while (++i < gnrl->nbr_of_philo)
		if (gnrl->philo[i].meal < gnrl->must_eat)
			return ;
	printf("\nall have eaten\n");
	gnrl->end = true;
}

void	monitor(t_gnrl *gnrl)
{
	while (1)
	{
		pthread_mutex_lock(&gnrl->monitor);
		all_eaten(gnrl);
		fnd_dead(gnrl);
		if (gnrl->end)
		{
			pthread_mutex_unlock(&gnrl->monitor);
			break ;
		}
		pthread_mutex_unlock(&gnrl->monitor);
		usleep(300);
	}
}

void	status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->gnrl->monitor);
	if (!philo->gnrl->end)
		printf("%5d %3d %s\n", now() - philo->gnrl->start, philo->id, msg);
	pthread_mutex_unlock(&philo->gnrl->monitor);
}
