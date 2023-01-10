/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:55:33 by gbierny           #+#    #+#             */
/*   Updated: 2023/01/10 15:29:48 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((int)(t.tv_sec * 1000) + (int)(t.tv_usec / 1000));
}

void	the_message(t_philo *philo, char *s)
{
	ft_putnbr(get_time() - philo->state->start);
	write(1, "\t", 1);
	ft_putnbr(philo->p_place + 1);
	write(1, s, ft_strlen(s));
}

int	display_message(t_philo *philo, char *s, int n)
{
	sem_wait(philo->state->sem_write);
	sem_wait(philo->state->sem_died);
	if (n)
	{
		the_message(philo, s);
		return (1);
	}
	the_message(philo, s);
	if (!n)
		sem_post(philo->state->sem_died);
	sem_post(philo->state->sem_write);
	return (0);
}

void	error_message(char *s)
{
	if (!s)
		exit(EXIT_FAILURE);
	write(2, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		error_message("number of arguments invalid");
	(void)argv;
	return (0);
}
