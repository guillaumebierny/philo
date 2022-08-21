/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:18:27 by gbierny           #+#    #+#             */
/*   Updated: 2022/08/18 04:27:48 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int f_take_fork(t_philo *philo)
{
    sem_wait(&philo->state->sem_fork);
    if (display_message(philo, "has taken a fork", 0))
        return (1);
    sem_wait(&philo->state->sem_write);
    if (display_message(philo,"has taken a fork", 0))
        return (1);
    return (0);
}

int f_eat(t_philo *philo)
{
    if (display_message(philo, "is eating", 0))
        return (1);
    philo->resting_time = get_time() + philo->state->time_to_die;
    usleep(philo->state->time_to_eat * 1000);
    sem_post(&philo->state->sem_fork);
    sem_post(&philo->state->sem_fork);
    return (0);
}

int f_sleep(t_philo *philo)
{
    if (display_message(philo, "is sleeping", 0))
        return (1);
    usleep(philo->state->time_to_sleep * 1000);
    display_message(philo, "is thinking", 0);
    return (0);
    
}

int routine(t_philo *philo)
{
    if(f_take_fork(philo))
        return (1);
    if (f_eat(philo))
        return (1);
    if (f_sleep(philo))
        return (1);
    return (0);
}

void    set_fork(t_philo *philo)
{
    pthread_t tid;
    pthread_create(&tid, NULL, check_death, (void *)philo);
    while (1)
    {   
        if (routine(philo))
        {
            pthread_join(tid, NULL);    
            exit(0);
        }
    }
    pthread_join(tid, NULL);
    exit(0);
}

void    start_fork(t_state *s)
{
    int i;
    
    i = 0;
     while (i < s->n_philo)
    {
        s->philo[i].pid = fork();
        if (s->philo[i].pid == 0)
            set_fork(&s->philo[i]);
        i++;
    }
}

int main(int argc, char **argv)
{
    int i;
    t_state state;
    pthread_t tid;
    
    tid = 0;
    i = 0;
    initialise_v(&state, argv, argc);
    if (argc == 6)
        pthread_create(&tid, NULL, check_last_meal, &state);
    start_fork(&state);
    if (argc == 6)
        pthread_join(tid, NULL);
    while (i < state.n_philo)
        waitpid(state.philo[i].pid, NULL, 0);
    return (0);
}