/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 08:55:06 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/07/10 09:29:50 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
drop fork is a must since take fork
may die while taking the fork then nothing should be updated
last_meal definiton: at the BEGINNING of the meal
*/
void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	status(philo, C_GRAY"has taken a fork"NC);
	pthread_mutex_lock(philo->l_fork);
	status(philo, C_GRAY"has taken a fork"NC);
	status(philo, C_ORANGE"is eating"NC);
	pthread_mutex_lock(&philo->gnrl->monitor);
	if (!philo->gnrl->end)
	{
		philo->last_meal = now();
		philo->meal++;
	}
	pthread_mutex_unlock(&philo->gnrl->monitor);
	ft_msleep(philo->gnrl->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleep_(t_philo *philo)
{
	status(philo, C_RED"is sleeping"NC);
	ft_msleep(philo->gnrl->time_to_sleep);
}

// if only a philo
// start in diff time is more efficient than take fork turn
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->gnrl->nbr_of_philo == 1)
	{
		status(philo, C_GRAY"has taken a fork"NC);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_msleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->gnrl->monitor);
		if (philo->gnrl->end)
		{
			pthread_mutex_unlock(&philo->gnrl->monitor);
			break ;
		}
		pthread_mutex_unlock(&philo->gnrl->monitor);
		eat(philo);
		sleep_(philo);
		status(philo, C_CYAN"is thinking"NC);
	}
	return (NULL);
}
