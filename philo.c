/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 21:55:14 by gbierny           #+#    #+#             */
/*   Updated: 2022/07/29 23:43:05 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	display_message(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->state->write);
	if (philo->state->dead)
	{
		printf("end of philo  %d\n", philo->p_place);
		return ;
	}
	ft_putnbr(get_time() - philo->state->start);
	write(1, "\t", 1);
	ft_putnbr(philo->p_place);
	write(1, s, ft_strlen(s));
	pthread_mutex_unlock(&philo->state->write);
}

void routine(t_philo *philo)
{
	take_fork(philo);
	eat(philo);
	sleep_think(philo);
}

int	start_the_routine(t_state *state)
{
	int i;
	pthread_t tid;
	// pthread_t *philo_thread;
	// if (!(philo_thread = malloc(sizeof(pthread_t) * state->n_philo)))
	// 	return ;
	i = 0;
	while (i < state->n_philo - 1)
	{
		pthread_create(&tid, NULL, philos_routine, &state->philo[i]);
		pthread_detach(tid);
		i += 2;
	}
	i = 1;
	usleep((state->time_to_eat - 1) * 1000);
	while (i < state->n_philo)
	{
		pthread_create(&tid, NULL, philos_routine, &state->philo[i]);
		pthread_detach(tid);
		i += 2;
	}
	if (state->n_philo % 2 == 1)
	{
		usleep((state->time_to_eat - 1) * 1000);
		pthread_create(&tid, NULL, philos_routine, &state->philo[state->n_philo - 1]);
		pthread_detach(tid);
	}
	// printf("VOILA MON I: %d\n", i);
	i = 0;
	// while (i < state->n_philo)
	// 	pthread_join(philo_thread[i++], NULL);
	// free(philo_thread);
	return (0);
}

void	*philos_routine(void *philo_var)
{
	pthread_t tid;
	t_philo *philo;

	philo = (t_philo *)philo_var;
	pthread_create(&tid, NULL, check_death, philo_var);
	pthread_detach(tid);
	if (philo->state->n_of_meal)
	{
		while (philo->resting_meal > 0)
			routine(philo);
		philo->state->still_hungry--;
		philo->full++;
	}
	else
	{	
		while(1)
			routine(philo);
	}
	printf("GROSSE END\n");
	return (0);
}

int get_time(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return ((int)(t.tv_sec * 1000) + (int)(t.tv_usec / 1000));
}

void	clean_thread(t_state *s)
{
	int i;

	i = 0;
	//printf("je\n");
	pthread_mutex_destroy(&s->write);
	//printf("suis\n");
	
	while (i < s->n_philo)
	{
		pthread_mutex_destroy(&s->fork[i++]);
	}
	//printf("la\n");
	free(s->fork);
	//printf("point\n");
	free(s->philo);
	//printf("a la ligne\n");
}

int main(int argc, char **argv)
{
	t_state state;
	pthread_t tid;

	if (argc < 5 || argc > 6)
		return(error_message("pas le bon nombre d'argument:\n"));
	if(init(&state, argv, argc))
		return(error_message("probleme avec l'initialisation des variables\n"));
	if (argc == 6)
	{
		pthread_create(&tid, NULL, check_last_meal, &state);
		pthread_detach(tid);
	}
	start_the_routine(&state);
	while (state.dead == 0)
		usleep(300);
	usleep(900);
	clean_thread(&state);
	return (0);
}
