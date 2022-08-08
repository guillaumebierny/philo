/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:38:48 by gbierny           #+#    #+#             */
/*   Updated: 2022/08/03 20:54:55 by gbierny          ###   ########.fr       */
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
        pthread_mutex_lock(&philo->temps);
		if (get_time() > philo->resting_time)
		{
			display_message(philo, " died\n", 1);
            f_unlock(philo->state);
            pthread_mutex_unlock(&philo->state->finish);
            return (0);
		}
        pthread_mutex_unlock(&philo->temps);
        usleep(10);
	}
    return (0);
}

// void	*check_last_meal(void *state_v)
// {
//     t_state *s;
//     int i;
//     int philo_still_hungry;

//     s = (t_state *)state_v;
//     philo_still_hungry = s->n_philo;
//     i = 0;
//     while (1)
//     {
//         pthread_mutex_lock(&s->still_hungry_m);
//         if (!s->still_hungry)
//             break;
//         pthread_mutex_unlock(&s->still_hungry_m);
//         usleep(50);
//     }
//     pthread_mutex_lock(&s->dead_m);
//     pthread_mutex_unlock(&s->dead_m);
//     pthread_mutex_lock(&s->write);
//     ft_putstr("every philo finished to eat\n");
//     return (0);
// }

void *check_last_meal(void *s_v)
{
    t_state *s;
    int i;
    int j;

    i = 0;
    s = (t_state *)s_v;
    while (i < s->n_of_meal)
    {
        j = 0;
        while (j < s->n_philo && !s->end)
            pthread_mutex_lock(&s->philo[j++].eat_m);
        i++;
    }
    if (s->end)
        return (0);
    pthread_mutex_lock(&s->write);
    s->end = 1;
    ft_putstr("every philo finish to eat\n");
    pthread_mutex_unlock(&s->finish);
    pthread_mutex_unlock(&s->write);
    return (0);
}
