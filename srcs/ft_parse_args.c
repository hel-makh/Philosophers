/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:44:41 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/08 18:14:23 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_isint(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9')
			&& str[i] != ' '
			&& str[i] != '-'
			&& str[i] != '+')
			return (0);
		i ++;
	}
	return (1);
}

static long	ft_atoi_ld(const char *str)
{
	long	sign;
	long	nbr;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\r' || *str == '\f')
		str ++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str ++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0');
		str ++;
	}
	return (sign * nbr);
}

static int	ft_atoi(const char *str)
{
	int	sign;
	int	nbr;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\r' || *str == '\f')
		str ++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str ++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0');
		str ++;
	}
	return (sign * nbr);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i ++;
	}
	return (0);
}

int	ft_parse_args(int argc, char *argv[], t_vars *vars)
{
	int		i;

	i = 1;
	while (i < argc && i < 5)
	{
		while (*argv[i] == ' ')
			*(argv + i) += 1;
		if (!ft_isint(argv[i]) || (ft_atoi_ld(argv[i]) == 0
				&& ft_strncmp(argv[i], "0", 1) && ft_strncmp(argv[i], "-0", 2)
				&& ft_strncmp(argv[i], "+0", 2)))
			return (0);
		i ++;
	}
	vars->args.philo_count = ft_atoi(argv[1]);
	vars->args.die_time = ft_atoi_ld(argv[2]);
	vars->args.eat_time = ft_atoi_ld(argv[3]);
	vars->args.sleep_time = ft_atoi_ld(argv[4]);
	vars->args.meals_count = 0;
	if (argc > 5)
		vars->args.meals_count = ft_atoi(argv[5]);
	if (vars->args.philo_count < 1 || vars->args.die_time < 1
		|| vars->args.eat_time < 1 || vars->args.sleep_time < 1
		|| vars->args.meals_count < 0)
		return (0);
	return (1);
}
