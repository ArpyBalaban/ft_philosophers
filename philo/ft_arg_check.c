/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:27:17 by abalaban          #+#    #+#             */
/*   Updated: 2022/02/13 20:10:49 by abalaban         ###   ########.fr       */
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

long	ft_atoi(const char *str)
{
	long	i;
	long	number;
	int		sign;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * sign);
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
