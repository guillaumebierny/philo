/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:38:48 by gbierny           #+#    #+#             */
/*   Updated: 2022/07/27 00:09:48 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *check_death(void *philo_v)
{
    t_philo *philo;

    philo = (t_philo *)philo_v;
	while (1)
	{
		if (get_time() > philo->resting_time)
		{
			display_message(philo, " died");
            philo->state->dead = 1;
		}
        usleep(100);
	}
}

void	*check_last_meal(void *state_v)
{
    t_state *s;
    int i;
    int philo_still_hungry;

    s = (t_state *)state_v;
    philo_still_hungry = s->n_philo;
    i = 0;
        while (philo_still_hungry--)
        {
            while (s->philo[i].resting_meal)
                usleep(100);
            i++;
            philo_still_hungry--;
        }
        pthread_mutex_lock(&s->write);
        ft_putstr("every philo finished to eat");
        s->dead = 1;
        pthread_exit(NULL);
}
