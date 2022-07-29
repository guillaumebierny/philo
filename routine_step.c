/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_step.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:27:47 by gbierny           #+#    #+#             */
/*   Updated: 2022/07/29 23:41:26 by gbierny          ###   ########.fr       */
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

void take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->fork[philo->p_place]);
	display_message(philo, " has taken a fork\n");
	pthread_mutex_lock(&philo->state->fork[(philo->p_place + 1) % philo->state->n_philo]);
	display_message(philo, " has taken a fork\n");
}

void eat(t_philo *philo)
{
	display_message(philo, " is eating\n");
	if (philo->state->dead == 1)
		return ;
	philo->resting_time = get_time() + philo->state->time_to_die;
	usleep(philo->state->time_to_eat * 1000);
	philo->resting_meal--;
	pthread_mutex_unlock(&philo->state->fork[philo->p_place]);
	pthread_mutex_unlock(&philo->state->fork[(philo->p_place + 1) % philo->state->n_philo]);
}

void sleep_think(t_philo *philo)
{
	display_message(philo, " is sleeping\n");
	usleep(philo->state->time_to_sleep * 1000);
	display_message(philo, " is thinking\n");
}