/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:20:49 by hel-makh          #+#    #+#             */
/*   Updated: 2022/01/31 19:20:49 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"
#include <stdio.h>

#include "srcs/ft_strcmp.c"
#include "srcs/ft_atoi.c"
#include "srcs/ft_atoi_ull.c"
#include "srcs/ft_calloc.c"
#include "srcs/ft_get_timestamp.c"

#include "srcs/ft_is_fork_surrounded.c"

void	ft_start_eating(t_vars *vars, int philo_id)
{
	t_philo	*philo;

	pthread_mutex_lock(&vars->mutex);
	if (!ft_is_fork_surrounded(vars, philo_id))
	{
		pthread_mutex_unlock(&vars->mutex);
		return ;
	}
	philo = &vars->philo[philo_id];
	philo->right_hand = 1;
	philo->left_hand = 1;
	printf("%llu_in_ms %d has taken a fork\n",
		ft_get_timestamp(NULL), philo_id + 1);
	printf("%llu_in_ms %d is eating\n",
		ft_get_timestamp(NULL), philo_id + 1);
	pthread_mutex_unlock(&vars->mutex);
	usleep(vars->args.eat_time * 1000);
	philo->last_meal = ft_get_timestamp(NULL);
}

void	ft_start_sleeping(t_vars *vars, int philo_id)
{
	t_philo	*philo;

	pthread_mutex_lock(&vars->mutex);
	philo = &vars->philo[philo_id];
	if (!philo->right_hand && !philo->left_hand)
	{
		pthread_mutex_unlock(&vars->mutex);
		return ;
	}
	philo->right_hand = 0;
	philo->left_hand = 0;
	printf("%llu_in_ms %d is sleeping\n",
		ft_get_timestamp(NULL), philo_id + 1);
	pthread_mutex_unlock(&vars->mutex);
	usleep(vars->args.sleep_time * 1000);
	printf("%llu_in_ms %d is thinking\n",
		ft_get_timestamp(NULL), philo_id + 1);
}

static void	*thread_start(void *arg)
{
	t_vars		*vars;
	int			philo_id;

	vars = (t_vars *)arg;
	pthread_mutex_lock(&vars->mutex);
	philo_id = vars->philo_id - 1;
	pthread_mutex_unlock(&vars->mutex);
	vars->philo[philo_id].last_meal = ft_get_timestamp(NULL);
	while (1)
	{
		if (vars->philo[philo_id].last_meal + vars->args.die_time
			<= ft_get_timestamp(NULL))
		{
			printf("%llu_in_ms %d died\n",
				ft_get_timestamp(NULL), philo_id + 1);
			exit(EXIT_SUCCESS);
		}
		if (ft_is_fork_surrounded(vars, philo_id))
		{
			ft_start_eating(vars, philo_id);
			ft_start_sleeping(vars, philo_id);
		}
	}
	return (NULL);
}

static void	philosophers(t_vars *vars)
{
	int	i;

	if (pthread_mutex_init(&vars->mutex, NULL) != 0)
		exit(EXIT_FAILURE);
	vars->philo = ft_calloc(vars->args.philo_count, sizeof(t_philo));
	if (!vars->philo)
		exit(EXIT_FAILURE);
	vars->philo_id = 0;
	while (vars->philo_id < vars->args.philo_count)
	{
		if (pthread_create(&vars->philo[vars->philo_id].thread, NULL,
				&thread_start, (void *)vars))
			exit(EXIT_FAILURE);
		vars->philo_id ++;
	}
	i = 0;
	while (i < vars->args.philo_count)
	{
		if (pthread_join(vars->philo[i].thread, NULL))
			exit(EXIT_FAILURE);
		i ++;
	}
	pthread_mutex_destroy(&vars->mutex);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	int		i;

	if (argc < 5)
		return (EXIT_FAILURE);
	i = 1;
	while (i < argc)
	{
		if (ft_atoi_ull(argv[i]) == 0 && ft_strcmp(argv[i], "0")
			&& ft_strcmp(argv[i], "-0") && ft_strcmp(argv[i], "+0"))
			return (EXIT_FAILURE);
		i ++;
	}
	vars.args.philo_count = ft_atoi(argv[1]);
	vars.args.die_time = ft_atoi_ull(argv[2]);
	vars.args.eat_time = ft_atoi_ull(argv[3]);
	vars.args.sleep_time = ft_atoi_ull(argv[4]);
	vars.args.eat_count = 0;
	if (argc > 5)
		vars.args.eat_count = ft_atoi(argv[5]);
	philosophers(&vars);
	exit(EXIT_SUCCESS);
}
