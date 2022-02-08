/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_mutex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:16:49 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/08 18:24:40 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_mutex_destroy(t_vars *vars, int index)
{
	while (index >= 0)
	{
		pthread_mutex_destroy(&vars->philo[index].right_fork);
		index --;
	}
	pthread_mutex_destroy(&vars->state_change);
	pthread_mutex_destroy(&vars->mutex);
}

void	ft_destroy_mutexes(t_vars *vars)
{
	ft_mutex_destroy(vars, vars->args.philo_count - 1);
}

int	ft_init_mutexes(t_vars *vars)
{
	int	i;
	int	j;

	if (pthread_mutex_init(&vars->mutex, NULL))
		return (0);
	if (pthread_mutex_init(&vars->state_change, NULL))
		return (pthread_mutex_destroy(&vars->mutex), 0);
	i = 0;
	while (i < vars->args.philo_count)
	{
		if (pthread_mutex_init(&vars->philo[i].right_fork, NULL))
			return (ft_mutex_destroy(vars, i - 1), 0);
		i ++;
	}
	i = 0;
	while (i < vars->args.philo_count)
	{
		j = i - 1;
		if (j < 0)
			j = vars->args.philo_count - 1;
		vars->philo[i].left_fork = &vars->philo[j].right_fork;
		i ++;
	}
	return (1);
}
