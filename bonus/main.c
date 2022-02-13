#include "philo.h"

void	starter(t_philo *philos)
{
	int status;
	int i;
	int count;

	i = 0;
	status = 0;
	count =philos[0].rules->philo_num;
	while (i < count)
	{
		philos[i].born_time_ms = get_time_ms();
		philos[i].pid = fork();
		if(philos[i].pid == 0)
			simulation(&philos[i]);
		else if (philos[i].pid < 0)
			ft_error("Couldn't oppen a fork");
		i++;
	}
	i = 0;
	while (i++ < count)
		waitpid(philos[i].pid, &status, 0);
	printf("All are full!\n");
}

int main (int argc, char **argv)
{
	t_philo			*philos;
	t_rules			rules;
	t_semaphore	sem;

	ft_arg_check(argc, argv);
	init_rules(&rules, argc, argv);
	if (rules.philo_num == 1)
	{
		printf("0 #1 died\n");
		return (0);
	}
	init_semaphore(&sem, rules.philo_num);
	philos = init_philos(&rules, &sem);
	starter(philos);
	end_process(philos, &sem);
	return (0);

}
