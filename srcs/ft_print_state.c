/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:25:39 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/09 19:30:44 by hel-makh         ###   ########.fr       */
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

void	ft_print_state(char *state, t_philo *philo, long timestamp)
{
	if (philo->vars->simulation_ended)
		return ;
	pthread_mutex_lock(&philo->vars->state_change);
	if (!philo->vars->simulation_ended)
	{
		printf("%ld %d %s\n", timestamp, philo->philo_id + 1, state);
		if (ft_strstr("died", state))
			philo->vars->simulation_ended = 1;
	}
	pthread_mutex_unlock(&philo->vars->state_change);
}
