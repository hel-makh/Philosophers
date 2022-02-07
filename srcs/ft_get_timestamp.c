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

t_timestamp	ft_get_timestamp(void)
{
	struct timeval	time;
	t_timestamp		timestamp;

	gettimeofday(&time, NULL);
	timestamp = time.tv_sec * 1000000;
	timestamp += time.tv_usec;
	timestamp /= 1000;
	return (timestamp);
}
