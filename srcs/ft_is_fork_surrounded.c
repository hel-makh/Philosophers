/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_fork_surrounded.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 23:09:20 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/01 23:09:20 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_is_fork_surrounded(t_vars *vars, int philo_id)
{
	t_philo	*philo;
	t_philo	*right_philo;
	t_philo	*left_philo;

	philo = &vars->philo[philo_id];
	if (philo_id + 1 >= vars->args.philo_count)
		right_philo = &vars->philo[0];
	else
		right_philo = &vars->philo[philo_id + 1];
	if (philo_id - 1 < 0)
		left_philo = &vars->philo[vars->args.philo_count - 1];
	else
		left_philo = &vars->philo[philo_id - 1];
	if (!philo->right_hand && !philo->left_hand
		&& !right_philo->left_hand && !left_philo->right_hand)
		return (1);
	return (0);
}
