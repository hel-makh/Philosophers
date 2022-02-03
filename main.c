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
#include "srcs/ft_free.c"
#include "srcs/ft_get_timestamp.c"

#include "srcs/ft_is_fork_surrounded.c"
#include "srcs/ft_meals_count_reached.c"
#include "srcs/ft_quit_program.c"

// int	ft_right_fork_taken(t_vars *vars, int philo_id)
// {
// 	t_philo	*right_philo;

// 	if (philo_id + 1 >= vars->args.philo_count)
// 		right_philo = &vars->philo[0];
// 	else
// 		right_philo = &vars->philo[philo_id + 1];
// 	if (right_philo->left_hand)
// 		return (1);
// 	return (0);
// }

void	ft_start_sleeping(t_vars *vars, int philo_id)
{
	t_philo	*philo;

	pthread_mutex_lock(&vars->mutex);
	philo = &vars->philo[philo_id];
	printf("%llu_in_ms %d is sleeping\n", ft_get_timestamp(NULL), philo_id + 1);
	philo->right_hand = 0;
	// while (!ft_right_fork_taken(vars, philo_id))
	// 	;
	// pthread_mutex_unlock(&vars->mutex);
	usleep(philo_id);
	// pthread_mutex_lock(&vars->mutex);
	philo->left_hand = 0;
	pthread_mutex_unlock(&vars->mutex);
	usleep(vars->args.sleep_time * 1000);
	pthread_mutex_lock(&vars->mutex);
	printf("%llu_in_ms %d is thinking\n", ft_get_timestamp(NULL), philo_id + 1);
	pthread_mutex_unlock(&vars->mutex);
}

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
	printf("%llu_in_ms %d has taken a fork\n",
		ft_get_timestamp(NULL), philo_id + 1);
	philo->left_hand = 1;
	printf("%llu_in_ms %d has taken a fork\n",
		ft_get_timestamp(NULL), philo_id + 1);
	philo->last_meal = ft_get_timestamp(NULL);
	printf("%llu_in_ms %d is eating\n", philo->last_meal, philo_id + 1);
	philo->meals_count ++;
	if (vars->args.meals_count && ft_meals_count_reached(*vars))
		ft_quit_program(EXIT_SUCCESS, vars, 1, 1);
	pthread_mutex_unlock(&vars->mutex);
	usleep(vars->args.eat_time * 1000);
	ft_start_sleeping(vars, philo_id);
}

static void	*thread_start(void *arg)
{
	t_vars		*vars;
	t_philo		*philo;
	int			philo_id;

	vars = (t_vars *)arg;
	pthread_mutex_lock(&vars->mutex);
	philo_id = vars->philo_id - 1;
	philo = &vars->philo[philo_id];
	philo->last_meal = ft_get_timestamp(NULL);
	printf("%llu_in_ms %d is thinking\n", philo->last_meal, philo_id + 1);
	pthread_mutex_unlock(&vars->mutex);
	while (1)
	{
		if (philo->last_meal + vars->args.die_time < ft_get_timestamp(NULL))
		{
			pthread_mutex_lock(&vars->mutex);
			printf("%llu_in_ms %d died\n", ft_get_timestamp(NULL), philo_id + 1);
			ft_quit_program(EXIT_SUCCESS, vars, 0, 0);
		}
		if (ft_is_fork_surrounded(vars, philo_id))
			ft_start_eating(vars, philo_id);
	}
	return (NULL);
}

static void	philosophers(t_vars *vars)
{
	int	i;

	vars->philo = ft_calloc(vars->args.philo_count, sizeof(t_philo));
	if (!vars->philo)
		exit(EXIT_FAILURE);
	if (pthread_mutex_init(&vars->mutex, NULL) != 0)
		ft_quit_program(EXIT_FAILURE, vars, 0, 0);
	vars->philo_id = 0;
	while (vars->philo_id < vars->args.philo_count)
	{
		if (pthread_create(&vars->philo[vars->philo_id].thread, NULL,
				&thread_start, (void *)vars))
			ft_quit_program(EXIT_FAILURE, vars, 0, 1);
		vars->philo_id ++;
	}
	i = 0;
	while (i < vars->args.philo_count)
	{
		if (pthread_join(vars->philo[i].thread, NULL))
			ft_quit_program(EXIT_FAILURE, vars, 0, 1);
		i ++;
	}
	pthread_mutex_destroy(&vars->mutex);
	ft_free(vars->philo);
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
	vars.args.meals_count = 0;
	if (argc > 5)
		vars.args.meals_count = ft_atoi(argv[5]);
	philosophers(&vars);
	return (EXIT_SUCCESS);
}
