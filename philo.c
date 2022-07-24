#include "philo.h"


void take_fork()
{
	pthread_mutex_lock(&left_fork)
	message();
	pthread_mutex_lock(rihgt_fork)
	message();
}


display_message()
{
	pthread_mutex_lock(&write);
	message(philo, time, action);
	pthread_mutex_unlock(&write);
}

void eat()
{
	display_message();
	usleep(philo->time_to_eat)
	before_to_die = get_time() + philo->time_to_die
}

void sleep_think()
{
	pthread_mutex_unlock(&lfork);
	pthread_mutex_unlock(&rfork);
	message();
	usleep(time_to_sleep);
	message();

}

void *check_death()
{
	while (1)
	{
		if (!philo->is_eating && get_time() > starving)
		{
			message("");
			pthread_mutex_unlock(philo->state->dead_m);
		}
	}
}

void	*check_last_meal()
{

}

void *philos_routine(void *philo_var, int )
{
	pthread_t tid;
	t_philo *philo;

	philo = (t_philo *)philo_var;
	pthread_create(&tid, NULL, check_death, NULL);
	pthread_detach(tid);
	if (philo->state->n_of_meal)
	while(1)
		routine();
	else
	while (philo->resting_meal-- < 0)
		routine();
}

void initialise_philo(t_state *s, t_philo *philo)
{
	int i;

	i = 0;
	while (i < s->n_philo)
	{
		s->philo[i].p_place = i;
		s->philo[i].is_eating = 0;
		s->philo[i].is_sleeping = 0;
		s->philo[i].state = s;
		s->philo[i].lfork = 0;
		s->philo[i].rfork = 0;
		s->philo[i].resting_meal = s->n_of_meal;

	}
}

void	init(t_state *s, char **argv, int argc)
{
	int i;

	i =
	s->n_philo = ft_atoi(argv[1]);
	s->time_to_die = ft_atoi(argv[2]);
	s->time_to_eat = ft_atoi(argv[3]);
	s->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		s->n_of_meal = ft_atoi(argv[5]);
	else
		s->n_of_meal = 0;
	if (s->n_philo <= 0 || s->time_to_die < 1)
		return (1);
	while (i < s->n_philo)
		s->philo = malloc(sizeof(t_philo) * s->n_philo);
	initialise_philo(s);
	pthread_mutex_init(&s->dead_m, NULL);
	pthread_mutex_lock(&s->dead_m);
}

int main(int argc, char **argv)
{
	t_state *state;
	init(state, argv);
	return (0);



}