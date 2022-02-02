/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_timestamp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:18:10 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/01 15:18:10 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_timestamp	ft_get_timestamp(t_timestamp *timest)
{
	struct timeval	time;
	t_timestamp 	timestamp;

	gettimeofday(&time, NULL);
	timestamp = time.tv_sec * 1000000;
	timestamp += time.tv_usec;
	timestamp /= 1000;
	if (timest)
		*timest = timestamp;
	return (timestamp);
}
