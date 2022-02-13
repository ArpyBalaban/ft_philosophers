/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:08:45 by abalaban          #+#    #+#             */
/*   Updated: 2022/02/13 17:11:25 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *str)
{
	long long	time;
	int			index;

	index = philo->index;
	time = get_time_ms() - philo->born_time_ms;
	printf("%lld #%d %s\n", time, index, str);
}

void	*is_live(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		sem_wait(philo->sem->end);
		if (get_time_ms() - philo->last_meal > philo->rules->die_t)
		{
			print_status(philo, "died");
			kill(0, SIGINT);
			return (NULL);
		}
		sem_post(philo->sem->end);
		usleep(1000);
	}
	return (NULL);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->rules->sleep_t * 1000);
	print_status(philo, "is thinking");
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->sem->fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "has taken another fork");
	philo->last_meal = get_time_ms();
	print_status(philo, "is eating");
	usleep(philo->rules->eat_t * 1000);
	sem_post(philo->sem->fork);
}

void	simulation(t_philo *philo)
{
	int			i;
	pthread_t	thread_id;

	i = philo->rules->eat_count;
	philo->last_meal = get_time_ms();
	pthread_create(&thread_id, NULL, &is_live, (void *)philo);
	while (i != 0)
	{
		philo_eat(philo);
		philo_sleep(philo);
		usleep(1000);
		if (i != -1)
			i--;
	}
	exit(0);
}
