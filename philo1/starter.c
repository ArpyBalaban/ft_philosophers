#include "philo.h"

void* simulation(void* arg)
{
	t_philo	*phi;
	t_rules	*rules;

	phi = (t_philo *) arg;
	rules = phi->rules;
	if (phi->id % 2)
		usleep(15000);
	while (!(rules->dead))
	{
		eat(phi);
		if (rules->already_ate)
			break;
		print_status(rules, phi, "is sleeping");
		ft_sleep(rules, rules->time_sleep);
		print_status(rules, phi, "is thinking");
	}
}

void sim_exit(t_rules *rules, t_philo *philos)
{
	int i;

	i = -1;
	while (++i < rules->nmbr_philos)
		pthread_join(philos[i].thread_id, NULL);
	i = -1;
	while (++i < rules->nmbr_philos)
		pthread_mutex_destroy(&(rules->forks[i]));
	pthread_mutex_destroy(&(rules->write));
}

void death_checker(t_rules *rules, t_philo *philo )
{
	int i;

	while (!(rules->already_ate))
	{
		i = -1;
		while (++i < rules->nmbr_philos && !(rules->dead))
		{
			pthread_mutex_lock(&(rules->meal));
			if ((get_time_ms() - philo[i].last_meal) > rules->time_death)
			{
				print_status(rules,& (philo[i]), "died");
				rules->dead = 1; 
			}
			pthread_mutex_unlock(&(rules->meal));
			usleep(100);
		}
		if (rules->dead)
		{
			break;
		}
		i = 0;
		while (rules->nmbr_eat != -1 && i < rules->nmbr_philos && philo[i].ate >= rules->nmbr_eat)
			i++;
		if (i == rules->nmbr_philos)
			rules->already_ate = 1;
	}

}

int starter(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = rules->philosophers;
	rules->first_time_stamp = get_time_ms();
	while (i < rules->nmbr_philos)
	{
		if(pthread_create(&(philo[i].thread_id), NULL, simulation, &(philo[i])))
			return (1);
		philo[i].last_meal = get_time_ms();
		i++;
	}
	death_checker(rules, rules->philosophers);
	sim_exit(rules, philo);
	return (0);
}
