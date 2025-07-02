/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiftyblue <fiftyblue@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:47:23 by fiftyblue         #+#    #+#             */
/*   Updated: 2024/07/07 12:25:38 by fiftyblue        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	all_digit(char *s)
{
	if (!s)
		return (false);
	while (*s)
		if (!is_digit(*s++))
			return (false);
	return (true);
}

bool	is_space(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

long	ft_atol(char *str)
{
	long	nbr;
	long	s;

	nbr = 0;
	s = 1;
	while (is_space(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			s *= -1;
	while (is_digit(*str))
		nbr = nbr * 10 + (*str++ - '0');
	return (nbr * s);
}

// time should not have +/- in my understanding
int	valid_av(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (printf("argc should be 5 or 6\n"), 0);
	av++;
	while (*av)
	{
		if (!all_digit(*av))
			return (printf("argv should be nbr only\n"), 0);
		if (ft_atol(*av) > INT_MAX || ft_atol(*av) < INT_MIN)
			return (printf("argv should within INT_RANGE\n"), 0);
		av++;
	}
	return (1);
}
