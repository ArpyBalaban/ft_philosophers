/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:52:46 by abalaban          #+#    #+#             */
/*   Updated: 2022/02/13 16:55:09 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_num(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_arg_check(int argc, char **argv)
{
	int		i;
	long	tmp;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		ft_error("Wrong number of arguments");
		return (1);
	}
	while (argv[i])
	{
		tmp = ft_atoi(argv[i]);
		if (!is_num(argv[i]))
		{
			ft_error("Arguments contain non-numeric charecters");
			return (1);
		}
		if (tmp < -2147483648 || tmp > 2147483647)
		{
			ft_error("numbers exceeding the limits of an integer");
			return (1);
		}
		i++;
	}
	return (0);
}
