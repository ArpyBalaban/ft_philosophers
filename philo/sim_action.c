/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 20:27:51 by abalaban          #+#    #+#             */
/*   Updated: 2022/02/13 20:49:47 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_rules *rules, t_philo *philo, char *str)
{
	int		id;
	long	time;

	if (philo->rules->dead)
		return ;
	id = philo->id;
	time = get_time_ms() - rules->first_time_stamp;
	printf("%ld #%d %s\n", time, id, str);
}

void	ft_sleep(t_rules *rules, long long time)
{
	long long	t;

	t = get_time_ms();
	while (!(rules->dead))
	{
		if ((get_time_ms() - t) >= time)
			break ;
		usleep(50);
	}
}

void	eat(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork]));
	print_status(rules, philo, "Has taken a fork");
	pthread_mutex_lock(&(rules->forks[philo->right_fork]));
	print_status(rules, philo, "Has taken another fork");
	pthread_mutex_lock(&(rules->meal));
	print_status(rules, philo, "is eating");
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&(rules->meal));
	ft_sleep(rules, rules->time_eat);
	(philo->ate)++;
	pthread_mutex_unlock(&(rules->forks[philo->right_fork]));
	pthread_mutex_unlock(&(rules->forks[philo->left_fork]));
}
