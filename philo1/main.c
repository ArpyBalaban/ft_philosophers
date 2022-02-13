#include "philo.h"

int main(int argc, char **argv)
{
	t_rules rules;
	int ret;
	
	if (ft_arg_check(argc, argv))
		return (1);
	if (init_all(&rules, argv))
		return (1);
	if (rules.nmbr_philos == 1)
	{
		printf("%d #1 died\n", rules.time_death);
		return (1);
	}
	if (ret = starter(&rules))
	{
		ft_error("Failed to start the threads!");
		return (ret);
	}

	return (4);
}
