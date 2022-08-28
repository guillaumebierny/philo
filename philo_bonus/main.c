/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:18:27 by gbierny           #+#    #+#             */
/*   Updated: 2022/08/28 23:34:18 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int get_time(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return ((int)(t.tv_sec * 1000) + (int)(t.tv_usec / 1000));
}

void the_message(t_philo *philo, char *s)
{
    ft_putnbr(get_time() - philo->state->start);
    write(1, "\t", 1);
    ft_putnbr(philo->p_place + 1);
    write(1, s, ft_strlen(s));    
}

int display_message(t_philo *philo, char *s, int n)
{
    sem_wait(philo->state->sem_write);
    sem_wait(philo->state->sem_died);
    if (n)
    {
        the_message(philo, s);
        return (1);
    }
    the_message(philo, s);
    if (!n)
        sem_post(philo->state->sem_died);
    sem_post(philo->state->sem_write);
    return (0);
}

int f_take_fork(t_philo *philo)
{
    sem_wait(philo->state->sem_fork);
    if (display_message(philo, " has taken a fork\n", 0))
    {
        return (1);
    }
    sem_wait(philo->state->sem_fork);
    if (display_message(philo," has taken a fork\n", 0))
        return (1);
    return (0);
}

int f_eat(t_philo *philo)
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

int f_sleep(t_philo *philo)
{
    if (display_message(philo, " is sleeping\n", 0))
        return (1);
    usleep(philo->state->time_to_sleep * 1000);
    display_message(philo, " is thinking\n", 0);
    return (0);
}

int routine(t_philo *philo)
{
    while (philo->current_meal > philo->state->gen_current_meal)
        usleep(10);
    if(f_take_fork(philo) ||
        f_eat(philo) ||
        f_sleep(philo))
        return (1);
    return (0);
}

void    set_fork(t_philo *philo)
{
    pthread_t tid;
    if (philo->p_place > philo->p_place / 2)
        usleep(philo->state->time_to_eat / 2);
    pthread_create(&tid, NULL, check_death, (void *)philo);
    while (1)
    {   
        if (routine(philo))
        {
            pthread_join(tid, NULL);
            printf("FINI LE TOUR\n");
            exit(0);
        }
    }
    pthread_join(tid, NULL);
    exit(0);
}

int   start_fork(t_state *s)
{
    int i;
    
    i = 0;
     while (i < s->n_philo)
    {
        s->philo[i].pid = fork();
        if (s->philo[i].pid < 0)
            return (1);
        if (s->philo[i].pid == 0)
            set_fork(&s->philo[i]);
        i++;
    }
    return (0);
}

void    error_message(char *s)
{
    if (!s)
        exit(EXIT_FAILURE);
    write(2, s, ft_strlen(s));
    exit(EXIT_FAILURE);
}

int check_args(int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        error_message("pas le bon nombre d'argument\n");
        (void)argv;
    return (0);
}

int main(int argc, char **argv)
{
    int i;
    t_state state;
    pthread_t tid;

    check_args(argc, argv);
    tid = 0;
    i = 0;
    initialise_v(&state, argv, argc);
    if (argc == 6)
    {
        pthread_create(&tid, NULL, check_last_meal, &state);
        pthread_detach(tid);
    }
    if (start_fork(&state))
        return (1);
    printf("\t\t\tsalut\n");
    sem_wait(state.sem_finish);
    while (i < state.n_philo)
        kill(state.philo[i++].pid, SIGKILL);
    
    return (0);
}