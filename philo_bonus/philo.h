/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 17:04:50 by abalaban          #+#    #+#             */
/*   Updated: 2022/02/13 17:08:37 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_semaphore
{
	sem_t	*fork;
	sem_t	*write;
	sem_t	*end;
}				t_semaphore;

typedef struct s_rules
{
	int	philo_num;
	int	die_t;
	int	eat_t;
	int	sleep_t;
	int	eat_count;
}			t_rules;

typedef struct s_philo
{
	pid_t			pid;
	int				index;
	long long		born_time_ms;
	long long		last_meal;
	t_semaphore		*sem;
	t_rules			*rules;

}				t_philo;

int			ft_isdigit(int c);
void		ft_free(char **str);
void		ft_error(char *msg);
void		cleanup(t_philo *philo, t_semaphore *sem);
int			ft_nbrlen(long n);
long		ft_atoi(const char *str);
long long	get_time_ms(void );
void		ft_usleep(int len);
void		*is_live(void *ptr);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		simulation(t_philo *philo);
void		launch_process(t_philo *philos);
void		init_semaphore(t_semaphore	*sem, int len);
void		init_rules(t_rules *rules, int argc, char **argv);
t_philo		*init_philos(t_rules *rules, t_semaphore *sem);
int			ft_arg_check(int argc, char **argv);
void		starter(t_philo *philos);
void		end_process(t_philo *philo, t_semaphore *sem);
char		**ft_split(const char	*s, char c);
#endif
