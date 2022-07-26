/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 21:55:14 by gbierny           #+#    #+#             */
/*   Updated: 2022/07/27 00:06:03 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	display_message(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->state->write);
	ft_putnbr(get_time() - philo->state->start);
	ft_putstr("\t");
	ft_putnbr(philo->p_place);
	ft_putstr(s);
	pthread_mutex_unlock(&philo->state->write);
}

void routine(t_philo *philo)
{
	take_fork(philo);
	eat(philo);
	sleep_think(philo);
}

void	start_the_routine(t_state *state)
{
	int i;
	pthread_t tid;
	
	i = 0;
	while (i < state->n_philo)
		pthread_create(&tid, NULL, philos_routine, &state->philo[i++]);
		
}

void	*philos_routine(void *philo_var)
{
	pthread_t tid;
	t_philo *philo;

	philo = (t_philo *)philo_var;
	pthread_create(&tid, NULL, check_death, philo_var);
	pthread_detach(tid);
	if (philo->state->n_of_meal)
	while(1)
		routine(philo);
	else
	while (philo->resting_meal-- < 0)
		routine(philo);
	pthread_exit(NULL);
}

int get_time(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return ((int)(t.tv_sec * 1000) + (int)(t.tv_usec / 1000));
}

int main(int argc, char **argv)
{
	t_state state;
	pthread_t tid;
	init(&state, argv, argc);
	if (argc == 6)
		pthread_create(&tid, NULL, check_last_meal, &state);
	start_the_routine(&state);
	while (!state.dead)
		usleep(100);
	// clean_fork();
	return (0);
}