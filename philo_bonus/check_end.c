/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 03:42:02 by gbierny           #+#    #+#             */
/*   Updated: 2022/08/29 22:38:06 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	while (1)
	{
		pthread_mutex_lock(&philo->mut_eat);
		if (get_time() > philo->resting_time)
		{
			display_message(philo, " died", 1);
			sem_post(philo->state->sem_finish);
			exit(0);
		}
		pthread_mutex_unlock(&philo->mut_eat);
		usleep(10);
	}
	exit(0);
}

void	*check_last_meal(void *state)
{
	int		i;
	int		j;
	t_state	*s;

	s = (t_state *)state;
	i = -1;
	printf("min nombre de repas: %d\n", s->n_of_meal);
	while (i++ < s->n_of_meal)
	{
		j = -1;
		while (j++ < s->n_philo)
		{
			sem_wait(s->sem_meal);
			printf("philo %d eat\n", j);
		}
	}
	sem_wait(s->sem_write);
	write(1, "every philo finish to eat", 25);
	exit(0);
	return (0);
}
