/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_step.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:53:04 by gbierny           #+#    #+#             */
/*   Updated: 2022/08/29 22:54:13 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	f_take_fork(t_philo *philo)
{
	sem_wait(philo->state->sem_fork);
	if (display_message(philo, " has taken a fork\n", 0))
	{
		return (1);
	}
	sem_wait(philo->state->sem_fork);
	if (display_message(philo, " has taken a fork\n", 0))
		return (1);
	return (0);
}

int	f_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mut_eat);
	if (display_message(philo, " is eating\n", 0))
		return (1);
	philo->resting_time = get_time() + philo->state->time_to_die;
	pthread_mutex_unlock(&philo->mut_eat);
	sem_post(philo->state->sem_meal);
	usleep(philo->state->time_to_eat * 1000);
	sem_post(philo->state->sem_fork);
	sem_post(philo->state->sem_fork);
	return (0);
}

int	f_sleep(t_philo *philo)
{
	if (display_message(philo, " is sleeping\n", 0))
		return (1);
	usleep(philo->state->time_to_sleep * 1000);
	display_message(philo, " is thinking\n", 0);
	return (0);
}

int	routine(t_philo *philo)
{
	while (philo->current_meal > philo->state->gen_current_meal)
		usleep(10);
	if (f_take_fork(philo)
		|| f_eat(philo)
		|| f_sleep(philo))
		return (1);
	return (0);
}
