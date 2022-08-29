/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbierny <gbierny@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 23:18:27 by gbierny           #+#    #+#             */
/*   Updated: 2022/08/29 22:56:26 by gbierny          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_fork(t_philo *philo)
{
	pthread_t	tid;

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

int	start_fork(t_state *s)
{
	int	i;

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

int	main(int argc, char **argv)
{
	int			i;
	t_state		state;
	pthread_t	tid;

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
	sem_wait(state.sem_finish);
	while (i < state.n_philo)
		kill(state.philo[i++].pid, SIGKILL);
	return (0);
}
