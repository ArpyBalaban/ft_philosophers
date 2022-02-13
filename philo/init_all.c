/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:12:16 by abalaban          #+#    #+#             */
/*   Updated: 2022/02/13 20:43:57 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->nmbr_philos;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->write), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->meal), NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_rules *rules)
{
	int	i;

	i = rules->nmbr_philos;
	while (--i >= 0)
	{
		rules->philosophers[i].id = i;
		rules->philosophers[i].ate = 0;
		rules->philosophers[i].left_fork = i;
		rules->philosophers[i].right_fork = (i + 1) % rules->nmbr_philos;
		rules->philosophers[i].last_meal = 0;
		rules->philosophers[i].rules = rules;
	}
	return (0);
}

int	init_all(t_rules *rules, char **argv)
{
	rules->nmbr_philos = ft_atoi(argv[1]);
	rules->time_death = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	rules->already_ate = 0;
	rules->dead = 0;
	if (rules->nmbr_philos < 1 || rules->time_death < 0 || rules->time_eat < 0 \
			|| rules->time_sleep < 0 || rules->nmbr_philos > 250)
		return (1);
	if (argv[5])
	{
		rules->nmbr_eat = ft_atoi(argv[5]);
		if (rules->nmbr_eat <= 0)
			return (2);
	}
	else
	{
		rules->nmbr_eat = -1;
	}
	if (init_mutex(rules))
		return (3);
	init_philosophers(rules);
	return (0);
}
