/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:29:59 by gbierny           #+#    #+#             */
/*   Updated: 2023/01/09 16:06:53 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialise_philo(t_state *s)
{
	int	i;

	i = 0;
	while (i < s->n_philo)
	{
		s->philo[i].p_place = i;
		s->philo[i].is_eating = 0;
		s->philo[i].is_sleeping = 0;
		s->philo[i].state = s;
		s->philo[i].resting_meal = s->n_of_meal;
		s->philo[i].resting_time = (s->start + s->time_to_die);
		s->philo[i].state = s;
		pthread_mutex_init(&s->philo[i].eat_m, NULL);
		pthread_mutex_lock(&s->philo[i].eat_m);
		pthread_mutex_init(&s->philo[i].temps, NULL);
		i++;
	}
}

int	check_atoi(int np, int ttd, int tte, int tts)
{
	if (np < 0)
		err_msg("number of philo argument is invalid\n");
	if (ttd < 0)
		err_msg("time to die argument is invalid\n");
	if (tte < 0)
		err_msg("time to eat argument is invalid\n");
	if (tts < 0)
		err_msg("time to sleep argument is invalid\n");
	if (np < 0 || ttd < 0 || tte < 0 || tts < 0)
		return (1);
	return (0);
}

int	initialisation_mutex(t_state *s)
{
	int	i;

	i = 0;
	s->fork = malloc(sizeof(pthread_mutex_t) * s->n_philo);
	if (!s->fork)
		return (err_msg("error: malloc fork\n"));
	pthread_mutex_init(&s->finish, NULL);
	pthread_mutex_lock(&s->finish);
	while (i < s->n_philo)
		pthread_mutex_init(&s->fork[i++], NULL);
	pthread_mutex_init(&s->write, NULL);
	return (0);
}

int	take_arguments_value(t_state *s, char **argv, int argc)
{
	s->n_philo = ft_atoi(argv[1]);
	s->time_to_die = ft_atoi(argv[2]);
	s->time_to_eat = ft_atoi(argv[3]);
	s->time_to_sleep = ft_atoi(argv[4]);
	if (check_atoi(s->n_philo, s->time_to_die,
			s->time_to_eat, s->time_to_sleep))
		return (1);
	if (argc == 6)
		s->n_of_meal = ft_atoi(argv[5]);
	else
		s->n_of_meal = 0;
	return (0);
}

int	init(t_state *s, char **argv, int argc)
{
	int	i;

	i = 0;
	if (take_arguments_value(s, argv, argc))
		return (1);
	if (s->n_of_meal < 0)
		return (err_msg("number of meal argument in invalid\n"));
	if (s->n_philo <= 0 || s->time_to_die < 1 || s->n_philo > 200
		|| s->time_to_die < 60 || s->time_to_eat < 60)
		return (err_msg("mauvais arguments\n"));
	s->philo = malloc(sizeof(t_philo) * s->n_philo);
	if (!s->philo)
		return (err_msg("error: malloc philo\n"));
	if (initialisation_mutex(s))
		return (1);
	s->start = get_time();
	s->end = 0;
	initialise_philo(s);
	return (0);
}
