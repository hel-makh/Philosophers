/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:25:39 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/09 00:42:25 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i + j] == needle[j])
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j ++;
		}
		i ++;
	}
	return (0);
}

void	ft_print_state(char *state, int philo_id, long timestamp, t_vars *vars)
{
	pthread_mutex_lock(&vars->state_change);
	if (!vars->simulation_ended)
		printf("%ld %d %s\n", timestamp, philo_id, state);
	if (ft_strstr("died", state))
		vars->simulation_ended = 1;
	pthread_mutex_unlock(&vars->state_change);
}
