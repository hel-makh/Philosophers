/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:23:17 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/08 00:11:23 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_msleep(long sleeptime)
{
	long	current_time;

	current_time = ft_get_timestamp();
	while (current_time + sleeptime > ft_get_timestamp())
		;
}