/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:29:59 by gbierny           #+#    #+#             */
/*   Updated: 2022/07/26 23:37:02 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void initialise_philo(t_state *s)
{
	int i;

	i = 0;
	while (i < s->n_philo)
	{
		s->philo[i].p_place = i;
		s->philo[i].is_eating = 0;
		s->philo[i].is_sleeping = 0;
		s->philo[i].state = s;
		s->philo[i].lfork = 0;
		s->philo[i].rfork = 0;
		s->philo[i].resting_meal = s->n_of_meal;
		s->philo[i].resting_meal = s->start + s->time_to_die;
		s->philo[i].state = s;
	}
}

void	init(t_state *s, char **argv, int argc)
{
	int i;

	i = 0;
	s->n_philo = ft_atoi(argv[1]);
	s->time_to_die = ft_atoi(argv[2]);
	s->time_to_eat = ft_atoi(argv[3]);
	s->time_to_sleep = ft_atoi(argv[4]);
	s->dead = 0;
	if (argc == 6)
		s->n_of_meal = ft_atoi(argv[5]);
	else
		s->n_of_meal = 0;
	if (s->n_philo <= 0 || s->time_to_die < 1)
		return (1);
	s->philo = malloc(sizeof(t_philo) * s->n_philo);
	while (i < s->n_philo)
	    initialise_philo(s);
    i = 0;
    if (!(s->fork = malloc(sizeof(pthread_mutex_t) * s->n_philo)))
        error_message("probleme de malloc des forks");
    while (i < s->n_philo)
        pthread_mutex_init(&s->fork[i], NULL);
	s->start = get_time();
}