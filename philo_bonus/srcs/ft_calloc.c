/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:31:33 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/14 20:31:33 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buffer;

	buffer = malloc (count * size);
	if (buffer == NULL)
		return (0);
	memset(buffer, 0, count * size);
	return (buffer);
}
