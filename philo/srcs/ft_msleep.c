/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 18:23:17 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/17 14:37:21 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static long	ft_get_timestamp(void)
{
	struct timeval	time;
	long			timestamp;

	gettimeofday(&time, NULL);
	timestamp = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (timestamp);
}

void	ft_msleep(long sleeptime)
{
	long	current_time;

	current_time = ft_get_timestamp();
	while (current_time + sleeptime >= ft_get_timestamp())
		usleep(40);
}
