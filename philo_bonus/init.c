/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:56:44 by abalaban          #+#    #+#             */
/*   Updated: 2022/02/13 17:01:05 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_semaphore(t_semaphore *sem, int len)
{
	sem_unlink("fork");
	sem_unlink("write");
	sem_unlink("end");
	sem->fork = sem_open("fork", O_CREAT | O_RDWR, 0660, len / 2);
	sem->write = sem_open("write", O_CREAT | O_RDWR, 0660, 1);
	sem->end = sem_open("end", O_CREAT | O_RDWR, 0660, 1);
}

void	init_rules(t_rules	*rules, int argc, char **argv)
{
	char	**args;
	int		i;

	i = 0;
	if (argc == 2)
		args = ft_split(argv[1], ' ');
	else
	{
		i = 1;
		args = argv;
	}
	rules->philo_num = ft_atoi(args[i]);
	rules->die_t = ft_atoi(args[i + 1]);
	rules->eat_t = ft_atoi(args[i + 2]);
	rules->sleep_t = ft_atoi(args[i + 3]);
	if (args[i + 4] != NULL)
			rules->eat_count = ft_atoi(args[i + 4]);
	else
		rules->eat_count = -1;
	if (argc == 2)
		ft_free(args);
}

t_philo	*init_philos(t_rules *rules, t_semaphore *sem)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * rules->philo_num);
	while (i < rules->philo_num)
	{
		philos[i].index = i + 1;
		philos[i].born_time_ms = 0;
		philos[i].last_meal = 0;
		philos[i].sem = sem;
		philos[i].rules = rules;
		i++;
	}
	return (philos);
}
