/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meals_count_reached.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 01:44:13 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/02 01:55:55 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_meals_count_reached(t_vars vars)
{
	int	i;

	i = 0;
	while (i < vars.args.philo_count)
	{
		if (vars.philo[i].meals_count < vars.args.meals_count)
			return (0);
		i ++;
	}
	return (1);
}
