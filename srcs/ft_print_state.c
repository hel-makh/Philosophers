/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:25:39 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/08 19:07:49 by hel-makh         ###   ########.fr       */
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

void	ft_print_state(t_vars *vars, char *state, int philo_id, long timestamp)
{
	pthread_mutex_lock(&vars->state_change);
	if (!vars->simulation_ended)
		printf("%ld %d %s\n", timestamp, philo_id + 1, state);
	if (ft_strstr("died", state))
		vars->simulation_ended = 1;
	pthread_mutex_unlock(&vars->state_change);
}
