/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:16:49 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/09 19:24:47 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_mutex_destroy(t_philo *philo, int index)
{
	while (index >= 0)
	{
		pthread_mutex_destroy(&philo[index].right_fork);
		index --;
	}
	pthread_mutex_destroy(&philo[0].vars->state_change);
}

void	ft_destroy_mutexes(t_philo *philo)
{
	ft_mutex_destroy(philo, philo[0].vars->args.philo_count - 1);
}

int	ft_init_mutexes(t_philo *philo)
{
	int	i;
	int	j;

	if (pthread_mutex_init(&philo[0].vars->state_change, NULL))
		return (0);
	i = 0;
	while (i < philo[0].vars->args.philo_count)
	{
		if (pthread_mutex_init(&philo[i].right_fork, NULL))
			return (ft_mutex_destroy(philo, i - 1), 0);
		i ++;
	}
	i = 0;
	while (i < philo[0].vars->args.philo_count)
	{
		j = i - 1;
		if (j < 0)
			j = philo[i].vars->args.philo_count - 1;
		philo[i].left_fork = &philo[j].right_fork;
		i ++;
	}
	return (1);
}
