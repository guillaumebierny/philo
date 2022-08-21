/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 03:42:02 by gbierny           #+#    #+#             */
/*   Updated: 2022/08/18 04:28:07 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *check_death(void *phi)
{
    t_philo philo;

    philo = *(t_philo *)phi;
    while (1)
    {
        if (get_time() > philo.resting_time)
        {
            exit(0);
        }
    }
    exit(0);
}

void    *check_last_meal(void *state)
{
    int i;
    t_state s;

    s = *(t_state *)state;
    i = 0;
    while (i < s.time_to_eat)
    {
        while (s.n_philo)
            sem_wait(&s.meal);
    }
    while (i < s.n_philo)
        kill(s.philo[i].pid, SIGKILL);
    return (0);
}