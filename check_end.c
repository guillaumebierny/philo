/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:38:48 by gbierny           #+#    #+#             */
/*   Updated: 2022/07/30 00:07:27 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *check_death(void *philo_v)
{
    t_philo *philo;
    int i;

    i = 0;
    philo = (t_philo *)philo_v;
	while (1)
	{
        pthread_mutex_lock(philo->state->eat_m);
        if (!philo->full && philo->state->dead == 0)
            break ;
		if (get_time() > philo->resting_time)
		{
			pthread_mutex_lock(&philo->state->write);
            if (philo->state->dead)
            {
                // printf("   fini  \n");
                usleep(100);
                pthread_exit(NULL);
            }
            ft_putnbr(get_time() - philo->state->start);
            write(1, "\t", 1);
            ft_putnbr(philo->p_place);
            write(1, " died\n", 6);
            philo->state->dead = 1;
            // pthread_mutex_unlock(&philo->state->write);
            // while (i < philo->state->n_philo)
            //     pthread_mutex_unlock(&philo->state->fork[i++]);
            // printf("fin de la mooort philo: %d\n", philo->p_place);
            return (0);
            
		}
        pthread_mutex_unlock(philo->state->eat_m)
        usleep(10);
	}
    // printf("stop philo: %d\n", philo->p_place);
    usleep(100);
    return (0);
}

void	*check_last_meal(void *state_v)
{
    t_state *s;
    int i;
    int philo_still_hungry;

    s = (t_state *)state_v;
    philo_still_hungry = s->n_philo;
    i = 0;
    while (s->still_hungry && s->dead == 0)
        usleep(50);
    if (s->dead)
        pthread_exit(NULL);
    pthread_mutex_lock(&s->write);
    s->dead = 1;
    ft_putstr("every philo finished to eat\n");
    pthread_exit(NULL);
}
