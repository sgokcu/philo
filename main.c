/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:43:37 by sgokcu            #+#    #+#             */
/*   Updated: 2024/08/31 19:32:37 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->hold->eat_mutex);
	philo->eat_count++;
	philo->last_eat = time_milisecond(philo->hold);
	pthread_mutex_unlock(&philo->hold->eat_mutex);
	ft_sleep(philo, philo->hold->time_to_eat);
}

int	to_do_continue(t_philosopher *philo)
{
	if (check_and_unlock(philo, 0) == 0)
		return (0);
	pthread_mutex_lock(philo->r_fork);
	if (check_and_unlock(philo, 1) == 0)
		return (0);
	my_printf(philo, "has taken a fork");
	if (check_and_unlock(philo, 1) == 0)
		return (0);
	pthread_mutex_lock(philo->l_fork);
	if (check_and_unlock(philo, 2) == 0)
		return (0);
	my_printf(philo, "has taken a fork");
	my_printf(philo, "is eating");
	if (check_and_unlock(philo, 2) == 0)
		return (0);
	return (1);
}

void	to_do(t_philosopher *philo)
{
	while (1)
	{
		if (to_do_continue(philo) == 0)
			break ;
		philo_eating(philo);
		if (check_and_unlock(philo, 2) == 0)
			break ;
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		my_printf(philo, "is sleeping");
		ft_sleep(philo, philo->hold->time_to_sleep);
		if (check_and_unlock(philo, 0) == 0)
			break ;
		my_printf(philo, "is thinking");
		if (check_and_unlock(philo, 0) == 0)
			break ;
	}
}

int	philo_make(t_hold *hold, int i)
{
	hold->start_time = 0;
	hold->dead_check = 1;
	hold->start_time = time_milisecond(hold);
	hold->philosopher = malloc(sizeof(t_philosopher) * hold->num_of_philo);
	hold->fork = malloc(sizeof(pthread_mutex_t) * hold->num_of_philo);
	while (++i < hold->num_of_philo)
		if (pthread_mutex_init(&hold->fork[i], NULL) != 0)
			return (0);
	pthread_mutex_init(&hold->eat_mutex, NULL);
	i = -1;
	while (++i < hold->num_of_philo)
	{
		hold->philosopher[i].pn = i + 1;
		hold->philosopher[i].r_fork = hold->fork + ((i + 1)
				% hold->num_of_philo);
		hold->philosopher[i].l_fork = hold->fork + i;
		hold->philosopher[i].hold = hold;
		hold->philosopher[i].status = ALIVE;
		hold->philosopher[i].eat_count = 0;
		hold->philosopher[i].last_eat = time_milisecond(hold);
		pthread_create(&hold->philosopher[i].thread, NULL, version,
			&hold->philosopher[i]);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_hold	hold;

	if (ac < 5 || ac > 6)
		return (printf("please enter a correct amount of args :)\n"));
	if (!ft_arg_check(av))
		return (printf(("please write args in the correct way :)\n")));
	placing(&hold, ac, av);
	if (hold.num_of_philo == 0)
		return (printf(("please write args in the correct way :)\n")));
	if (p_control(&hold) == 0)
		return (0);
	return (1);
}
