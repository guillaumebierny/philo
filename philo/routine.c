/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:07:39 by gbierny           #+#    #+#             */
/*   Updated: 2022/08/29 22:08:15 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine(t_philo *philo)
{
	if (take_fork(philo))
		return (1);
	if (eat(philo))
		return (1);
	if (sleep_think(philo))
		return (1);
	return (0);
}

void	launch_thread(pthread_t *philo_thread, int *i, t_state *state)
{
	pthread_create(&philo_thread[*i], NULL, philos_routine,
		&state->philo[*i]);
		(*i) += 2;
}

int	start_the_routine(t_state *state)
{
	int			i;
	pthread_t	*philo_thread;

	philo_thread = malloc(sizeof(pthread_t) * state->n_philo);
	i = 0;
	while (i < state->n_philo - 1)
		launch_thread(philo_thread, &i, state);
	i = 1;
	usleep((state->time_to_eat - 1) * 1000);
	while (i < state->n_philo)
		launch_thread(philo_thread, &i, state);
	if (state->n_philo % 2 == 1)
	{
		usleep((state->time_to_eat - 1) * 1000);
		pthread_create(&philo_thread[(state->n_philo - 1)], NULL,
			philos_routine, &state->philo[state->n_philo - 1]);
	}
	i = 0;
	while (i < state->n_philo)
		pthread_join(philo_thread[i++], NULL);
	free(philo_thread);
	return (0);
}

void	*philos_routine(void *philo_var)
{
	pthread_t	thid;
	t_philo		*philo;

	philo = (t_philo *)philo_var;
	pthread_create(&thid, NULL, check_death, philo_var);
	while (1)
	{
		if (routine(philo))
		{
			pthread_join(thid, NULL);
			f_unlock(philo->state);
			return (0);
		}
	}
	pthread_join(thid, NULL);
	f_unlock(philo->state);
	return (0);
}
