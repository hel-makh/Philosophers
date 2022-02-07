/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quit_program.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 02:08:33 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/02 02:08:33 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_return_error(
	int status, t_vars *vars, int unlock_mutex, int destroy_mutex
	)
{
	ft_free(vars->philo);
	if (unlock_mutex)
		pthread_mutex_unlock(&vars->mutex);
	if (destroy_mutex)
		pthread_mutex_destroy(&vars->mutex);
	return (status);
}
