/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_step.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:27:47 by gbierny           #+#    #+#             */
/*   Updated: 2022/08/02 13:11:48 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	even_case(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->state->fork[philo->p_place]);
// 	display_message(philo, " has taken a lfork\n");
// 	pthread_mutex_lock(&philo->state->fork[(philo->p_place + 1) % philo->state->n_philo]);
// 	display_message(philo, " has taken a rfork\n");
// }

// void	odd_case(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->state->fork[(philo->p_place + 1) % philo->state->n_philo]);
// 	display_message(philo, " has taken a rfork\n");
// 	pthread_mutex_lock(&philo->state->fork[philo->p_place]);
// 	display_message(philo, " has taken a lfork\n");
// }

// void take_fork(t_philo *philo)
// {
// 	if (philo->p_place % 2)
// 		even_case(philo);
// 	else
// 		odd_case(philo);
// }

int take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->fork[philo->p_place]);
	if (display_message(philo, " has taken a fork\n", 0))
		return (1);
	pthread_mutex_lock(&philo->state->fork[(philo->p_place + 1) % philo->state->n_philo]);
	if (display_message(philo, " has taken a fork\n", 0))
		return (1);
	return (0);
}

int eat(t_philo *philo)
{
	if (display_message(philo, " is eating\n", 0))
		return (1);
	pthread_mutex_lock(&philo->temps);
	philo->resting_time = get_time() + philo->state->time_to_die;
	pthread_mutex_unlock(&philo->temps);
	usleep(philo->state->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->eat_m);
	pthread_mutex_unlock(&philo->state->fork[philo->p_place]);
	pthread_mutex_unlock(&philo->state->fork[(philo->p_place + 1) % philo->state->n_philo]);
	return (0);
}

int sleep_think(t_philo *philo)
{
	if (display_message(philo, " is sleeping\n", 0))
		return (1);
	usleep(philo->state->time_to_sleep * 1000);
	if (display_message(philo, " is thinking\n", 0))
		return (1);
	return (0);
}