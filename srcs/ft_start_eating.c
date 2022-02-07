/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_eating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:15:37 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/05 18:17:29 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_start_eating(t_vars *vars, int philo_id)
{
	t_philo	*philo;

	pthread_mutex_lock(&vars->mutex);
	if (!ft_is_fork_surrounded(vars, philo_id))
	{
		pthread_mutex_unlock(&vars->mutex);
		return (EXIT_FAILURE);
	}
	philo = &vars->philo[philo_id];
	philo->right_hand = 1;
	printf("%llu %d has taken a fork\n", ft_get_timestamp(), philo_id + 1);
	philo->left_hand = 1;
	printf("%llu %d has taken a fork\n", ft_get_timestamp(), philo_id + 1);
	philo->last_meal = ft_get_timestamp();
	printf("%llu %d is eating\n", philo->last_meal, philo_id + 1);
	philo->meals_count ++;
	if (vars->args.meals_count && ft_meals_count_reached(*vars))
	{
		pthread_mutex_unlock(&vars->mutex);
		return (-1);
	}
	pthread_mutex_unlock(&vars->mutex);
	ft_usleep(vars->args.eat_time);
	ft_start_sleeping(vars, philo_id);
	return (EXIT_SUCCESS);
}
