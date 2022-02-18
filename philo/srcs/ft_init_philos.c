/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:06:59 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/18 15:17:22 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*ft_init_philos(t_vars *vars)
{
	t_philo	*philo;
	int		i;

	philo = ft_calloc(vars->args.philo_count, sizeof(t_philo));
	if (!philo)
		return (NULL);
	i = 0;
	while (i < vars->args.philo_count)
	{
		philo[i].id = i;
		philo[i].vars = vars;
		i ++;
	}
	return (philo);
}
