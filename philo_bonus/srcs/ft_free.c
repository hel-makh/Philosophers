/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:31:51 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/14 20:31:52 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*ft_free(void *ptr)
{
	free(ptr);
	return (NULL);
}

void	*ft_free_2d(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (NULL);
}

void	*ft_free_3d(void ***ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		ft_free_2d(ptr[i++]);
	return (NULL);
}
