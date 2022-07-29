/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:29:59 by gbierny           #+#    #+#             */
/*   Updated: 2022/07/30 00:09:43 by gbierny          ###   ########.fr       */
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
		s->philo[i].resting_meal = s->n_of_meal;
		s->philo[i].resting_time = s->start + s->time_to_die;
		s->philo[i].state = s;
		s->philo[i].full = 0;
		i++;
		pthread_mutex_init(&s->philo[i].eat_m, NULL);
	}
}

int	init(t_state *s, char **argv, int argc)
{
	int i;

	i = 0;
	s->n_philo = ft_atoi(argv[1]);
	s->time_to_die = ft_atoi(argv[2]);
	s->time_to_eat = ft_atoi(argv[3]);
	s->time_to_sleep = ft_atoi(argv[4]);
	s->still_hungry = s->n_philo;
	s->dead = 0;
	if (argc == 6)
		s->n_of_meal = ft_atoi(argv[5]);
	else
		s->n_of_meal = 0;
	if (s->n_philo <= 0 || s->time_to_die < 1 || s->n_philo > 200)
		return (error_message("mauvais arguments"));
	if(!(s->philo = malloc(sizeof(t_philo) * s->n_philo)))
		return (error_message("error: malloc philo"));
    i = 0;
    if (!(s->fork = malloc(sizeof(pthread_mutex_t) * s->n_philo)))
        return (error_message("error: malloc fork"));
    while (i < s->n_philo)
        pthread_mutex_init(&s->fork[i++], NULL);
	pthread_mutex_init(&s->write, NULL);
	s->start = get_time();
	initialise_philo(s);
	return (0);
}