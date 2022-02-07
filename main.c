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

// #include "srcs/ft_strncmp.c"
// #include "srcs/ft_isint.c"
// #include "srcs/ft_atoi.c"
// #include "srcs/ft_atoi_ld.c"
// #include "srcs/ft_calloc.c"
// #include "srcs/ft_free.c"
// #include "srcs/ft_get_timestamp.c"

// #include "srcs/ft_is_fork_surrounded.c"
// #include "srcs/ft_meals_count_reached.c"
// #include "srcs/ft_start_eating.c"
// #include "srcs/ft_start_sleeping.c"
// #include "srcs/ft_return_error.c"

static void	*start_simulation(void *arg)
{
	t_vars		*vars;
	t_philo		*philo;
	int			philo_id;

	vars = (t_vars *)arg;
	pthread_mutex_lock(&vars->mutex);
	philo_id = vars->philo_id;
	vars->philo[vars->philo_id].philo_id = vars->philo_id + 1;
	philo = &vars->philo[philo_id];
	philo->last_meal = ft_get_timestamp();
	printf("%ld %d is thinking\n", philo->last_meal, philo_id + 1);
	pthread_mutex_unlock(&vars->mutex);
	while (1)
	{
		if (philo->last_meal + vars->args.die_time < ft_get_timestamp())
		{
			pthread_mutex_lock(&vars->mutex);
			printf("%ld %d died\n", ft_get_timestamp(), philo_id + 1);
			break ;
		}
		if (ft_is_fork_surrounded(vars, philo_id))
			if (ft_start_eating(vars, philo_id) == -1)
				break ;
	}
	return (EXIT_SUCCESS);
}

static int	philosophers(t_vars *vars)
{
	vars->philo = ft_calloc(vars->args.philo_count, sizeof(t_philo));
	if (!vars->philo)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&vars->mutex, NULL))
		return (ft_return_error(EXIT_FAILURE, vars, 0, 0));
	vars->philo_id = 0;
	while (vars->philo_id < vars->args.philo_count)
	{
		if (pthread_create(&vars->philo[vars->philo_id].thread, NULL,
				&start_simulation, (void *)vars))
			return (ft_return_error(EXIT_FAILURE, vars, 0, 1));
		while (!vars->philo[vars->philo_id].philo_id)
			;
		vars->philo_id ++;
	}
	vars->philo_id = 0;
	while (vars->philo_id < vars->args.philo_count)
	{
		if (pthread_join(vars->philo[vars->philo_id].thread, NULL))
			return (ft_return_error(EXIT_FAILURE, vars, 0, 1));
		vars->philo_id ++;
	}
	return (ft_return_error(EXIT_SUCCESS, vars, 0, 1));
}

static void	ft_get_args(int argc, char *argv[], t_vars *vars)
{
	vars->args.philo_count = ft_atoi(argv[1]);
	vars->args.die_time = ft_atoi_ld(argv[2]);
	vars->args.eat_time = ft_atoi_ld(argv[3]);
	vars->args.sleep_time = ft_atoi_ld(argv[4]);
	vars->args.meals_count = 0;
	if (argc > 5)
		vars->args.meals_count = ft_atoi(argv[5]);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	int		i;

	if (argc < 5)
		return (EXIT_FAILURE);
	i = 1;
	while (i < argc && i < 5)
	{
		while (*argv[i] == ' ')
			*(argv + i) += 1;
		if (!ft_isint(argv[i]) || (ft_atoi_ld(argv[i]) == 0
				&& ft_strncmp(argv[i], "0", 1) && ft_strncmp(argv[i], "-0", 2)
				&& ft_strncmp(argv[i], "+0", 2)))
			return (EXIT_FAILURE);
		i ++;
	}
	ft_get_args(argc, argv, &vars);
	if (vars.args.philo_count < 1 || vars.args.die_time < 1
		|| vars.args.eat_time < 1 || vars.args.sleep_time < 1
		|| vars.args.meals_count < 0)
		return (EXIT_FAILURE);
	return (philosophers(&vars));
}
