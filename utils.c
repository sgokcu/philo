/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgokcu <sgokcu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:48:24 by sgokcu            #+#    #+#             */
/*   Updated: 2024/08/31 14:49:38 by sgokcu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' )
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		res = str[i] - '0' + res * 10;
		i++;
	}
	return (res * sign);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_arg_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		while (av[i][j])
		{
			if (ft_isalpha(av[i][j]))
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void	placing(t_hold *hold, int ac, char **av)
{
	int	i;

	i = 1;
	hold->num_of_philo = ft_atoi(av[i++]);
	hold->time_to_die = ft_atoi(av[i++]);
	hold->time_to_eat = ft_atoi(av[i++]);
	hold->time_to_sleep = ft_atoi(av[i++]);
	if (ac == 6)
		hold->num_must_eat = ft_atoi(av[i]);
	else
		hold->num_must_eat = -1;
}

void	*version(void *p)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)p;
	if (philo->hold->num_of_philo == 1)
	{
		ft_sleep(philo, philo->hold->time_to_die);
		p_check(philo);
		usleep(2000);
	}
	if (philo->pn % 2 == 0)
		usleep(750);
	to_do(philo);
	return (NULL);
}
