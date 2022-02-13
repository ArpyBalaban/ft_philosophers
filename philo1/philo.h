#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

struct s_rules;

typedef struct s_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	int				ate;
	long long		last_meal;
	pthread_t		thread_id;
	struct s_rules	*rules;
} 					t_philo;

typedef struct s_rules 
{
	int				nmbr_philos;
	int				nmbr_eat;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				already_ate;
	int				dead;
	long long		first_time_stamp;
	
	pthread_mutex_t	write;
	pthread_mutex_t	meal;
	pthread_mutex_t	forks[250];
	t_philo			philosophers[250];
}				t_rules;

int			ft_arg_check(int argc, char **argv);
void		ft_error(char *string);
int			init_all(t_rules *rules, char **argv);
long		ft_atoi(const char *str);
long long	get_time_ms(void);
int			starter(t_rules *rules);
int			eat(t_philo *philo);
void		print_status(t_rules *rules, t_philo *philo, char* str);
void		ft_sleep(t_rules *rules, long long time);
void		death_checker(t_rules *rules, t_philo *philo);
void		sim_exit(t_rules *rules, t_philo *philos);

#endif
