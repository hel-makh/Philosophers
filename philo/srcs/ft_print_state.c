/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:25:39 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/18 16:57:33 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	strlen;

	strlen = 0;
	while (s[strlen] != '\0')
		strlen ++;
	return (strlen);
}

static void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		write(fd, "-", 1);
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
	{
		nb += '0';
		write(fd, &nb, 1);
	}
}

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

void	ft_print_state(char *state, t_philo *philo)
{
	if (philo->vars->simulation_ended)
		return ;
	pthread_mutex_lock(&philo->vars->state_change);
	if (!philo->vars->simulation_ended)
	{
		ft_putnbr_fd(ft_get_current_time(philo->vars), STDOUT_FILENO);
		write(STDOUT_FILENO, " ", 1);
		ft_putnbr_fd(philo->id + 1, STDOUT_FILENO);
		write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, state, ft_strlen(state));
		write(STDOUT_FILENO, "\n", 1);
		if (ft_strstr("died", state))
			philo->vars->simulation_ended = 1;
	}
	pthread_mutex_unlock(&philo->vars->state_change);
}
