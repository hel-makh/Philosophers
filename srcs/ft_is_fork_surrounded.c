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
	int		right_philo_id;
	int		left_philo_id;

	philo = &vars->philo[philo_id];
	right_philo_id = philo_id + 1;
	if (right_philo_id >= vars->args.philo_count)
		right_philo_id = 0;
	left_philo_id = philo_id - 1;
	if (left_philo_id < 0)
		left_philo_id = vars->args.philo_count - 1;
	if (right_philo_id == left_philo_id)
		return (0);
	if (!philo->right_hand && !philo->left_hand
		&& !vars->philo[right_philo_id].left_hand
		&& !vars->philo[left_philo_id].right_hand)
		return (1);
	return (0);
}
