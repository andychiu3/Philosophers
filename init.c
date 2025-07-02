/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:20:40 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/07/03 14:57:46 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutex(pthread_mutex_t *mutex, int i)
{
	while (i--)
		pthread_mutex_destroy(&mutex[i]);
	free (mutex);
}

// nothing will happen if philo <= 0
int	init_philo(t_gnrl *gnrl)
{
	int	i;

	gnrl->philo = malloc(sizeof(t_philo) * gnrl->nbr_of_philo);
	if (!gnrl->philo)
		return (0);
	i = -1;
	while (++i < gnrl->nbr_of_philo)
	{
		gnrl->philo[i].id = i + 1;
		gnrl->philo[i].meal = 0;
		gnrl->philo[i].l_fork = &gnrl->fork[i];
		gnrl->philo[i].r_fork = &gnrl->fork[(i + 1) % gnrl->nbr_of_philo];
		gnrl->philo[i].last_meal = now();
		gnrl->philo[i].eating = false;
		gnrl->philo[i].gnrl = gnrl;
	}
	return (1);
}

int	init_fork(t_gnrl *gnrl)
{
	int	i;

	gnrl->fork = malloc(sizeof(pthread_mutex_t) * (gnrl->nbr_of_philo));
	if (!gnrl->fork)
		return (0);
	i = -1;
	while (++i < gnrl->nbr_of_philo)
	{
		if (pthread_mutex_init(&gnrl->fork[i], NULL) != 0)
		{
			free_mutex(gnrl->fork, i);
			return (0);
		}
	}
	return (1);
}

int	init_av(t_gnrl *gnrl, char **av)
{
	memset(gnrl, 0, sizeof(*gnrl));
	gnrl->nbr_of_philo = ft_atol(av[1]);
	if (gnrl->nbr_of_philo == 0)
		return (0);
	gnrl->time_to_die = ft_atol(av[2]);
	gnrl->time_to_eat = ft_atol(av[3]);
	gnrl->time_to_sleep = ft_atol(av[4]);
	gnrl->must_eat = -1;
	if (av[5])
		gnrl->must_eat = ft_atol(av[5]);
	if (gnrl->must_eat == 0)
		return (0);
	if (pthread_mutex_init(&gnrl->monitor, NULL))
		return (0);
	return (1);
}
