/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:47:55 by sgokcu            #+#    #+#             */
/*   Updated: 2024/08/31 19:33:09 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philosopher *p, long time)
{
	long	dest_time;

	dest_time = time_milisecond(p->hold) + time;
	while (time_milisecond(p->hold) < dest_time)
		usleep(500);
}

void	p_check(t_philosopher *p)
{
	pthread_mutex_lock(&p->hold->eat_mutex);
	if ((time_milisecond(p->hold) - p->last_eat) >= p->hold->time_to_die)
		p->status = DEAD;
	pthread_mutex_unlock(&p->hold->eat_mutex);
}

void	my_printf(t_philosopher *philosopher, char	*msg)
{
	pthread_mutex_lock(&philosopher->hold->eat_mutex);
	printf("%ld\t%d %s\n", time_milisecond(philosopher->hold),
		philosopher->pn, msg);
	pthread_mutex_unlock(&philosopher->hold->eat_mutex);
}

long	time_milisecond(t_hold	*hold)
{
	gettimeofday(&hold->time_val, NULL);
	return ((hold->time_val.tv_usec / 1000
			+ hold->time_val.tv_sec * 1000) - hold->start_time);
}

int	my_exit(t_hold *hold)
{
	int	i;

	i = -1;
	while (++i < hold->num_of_philo)
		pthread_join(hold->philosopher[i].thread, NULL);
	free (hold->philosopher);
	free (hold->fork);
	pthread_mutex_destroy(&hold->eat_mutex);
	return (0);
}
