#include "philo.h"

int to_do(t_philosopher *philo)
{
	while(1)
	{
		pthread_mutex_lock(philo->r_fork);
		my_printf(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		my_printf(philo, "has taken a fork");
		my_printf(philo, "is eating");
		pthread_mutex_lock(&philo->hold->eat_mutex);
		philo->eat_count++;
		philo->last_eat = time_milisecond(philo->hold);
		pthread_mutex_unlock(&philo->hold->eat_mutex);
		ft_sleep(philo, philo->hold->time_to_eat);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		my_printf(philo, "is sleeping");
		ft_sleep(philo, philo->hold->time_to_sleep);
		my_printf(philo, "is thinking");
	}
}

int	check_status(t_hold *hold, int i)
{
	while (++i < hold->number_of_philosophers)
	{
		f_check(&hold->philosopher[i]);
		pthread_mutex_lock(&hold->eat_mutex);
		if (hold->philosopher[i].status == DEAD)
		{
			printf("%ld\t%d died\n", time_milisecond(hold),
				hold->philosopher[i].pn);
			return (0);
		}
		pthread_mutex_unlock(&hold->eat_mutex);
	}
	i = -1;
	pthread_mutex_lock(&hold->eat_mutex);
	while (hold->number_of_times_each_philosopher_must_eat != -1 && ++i < hold->number_of_philosophers)
		if (hold->philosopher[i].eat_count < hold->number_of_times_each_philosopher_must_eat)
			break ;
	if (hold->number_of_times_each_philosopher_must_eat != -1 && i == hold->number_of_philosophers)
		return (0);
	pthread_mutex_unlock(&hold->eat_mutex);
	return (0);
}
int philo_make(t_hold *hold, int i)
{
	hold->start_time = 0;
	hold->start_time = time_milisecond(hold);
	hold->philosopher = malloc(sizeof(t_philosopher) * hold->number_of_philosophers);
	hold->fork = malloc(sizeof(pthread_mutex_t) * hold->number_of_philosophers);
	while(++i < hold->number_of_philosophers)
		if(pthread_mutex_init(&hold->fork[i], NULL) != 0)
			return (0);
	if(pthread_mutex_init(&hold->eat_mutex, NULL) != 0)
		return (0);
	i = -1;
	while(++i < hold->number_of_philosophers)
	{
		hold->philosopher[i].pn = i + 1;
		hold->philosopher[i].r_fork = hold->fork + ((i + 1)
				% hold->number_of_philosophers);
		hold->philosopher[i].l_fork = hold + i;
		hold->philosopher[i].status = ALIVE;
				hold->philosopher[i].hold = hold;
		hold->philosopher[i].eat_count = 0;
		hold->philosopher[i].last_eat = time_milisecond(hold);
		pthread_create(&hold->philosopher[i].thread, NULL, version,
			&hold->philosopher[i]);
	}
	return (1);
}

int p_control(t_hold *hold)
{
	int c;

	c = 1;
	if(!philo_make(hold, -1))
		c = my_exit(hold);
	while(1)
		if(!check_status(hold, -1))
			c = my_exit(hold);
	return (c);
}

int main(int ac, char **av)
{
	t_hold hold;

	if(ac < 5 || ac > 6)
		return(printf("please enter a correct amaont of args :)\n"));
	if(!ft_arg_check(av))
		return (printf(("plese write args in the correct way :)\n")));
	placing(&hold, ac, av);
	if(!p_control(&hold))
		return (0);

	
}
