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

// #include "srcs/ft_strcmp.c"
// #include "srcs/ft_isint.c"
// #include "srcs/ft_atoi.c"
// #include "srcs/ft_atoi_ull.c"
// #include "srcs/ft_calloc.c"
// #include "srcs/ft_free.c"
// #include "srcs/ft_get_timestamp.c"

// #include "srcs/ft_is_fork_surrounded.c"
// #include "srcs/ft_meals_count_reached.c"
// #include "srcs/ft_start_eating.c"
// #include "srcs/ft_start_sleeping.c"
// #include "srcs/ft_quit_program.c"

static void	*start_simulation(void *arg)
{
	t_vars		*vars;
	t_philo		*philo;
	int			philo_id;

	vars = (t_vars *)arg;
	pthread_mutex_lock(&vars->mutex);
	philo_id = vars->philo_id - 1;
	philo = &vars->philo[philo_id];
	if (philo_id == 0)
		philo->last_meal = ft_get_timestamp(NULL);
	philo->last_meal = vars->philo[0].last_meal;
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
				&start_simulation, (void *)vars))
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

static void	ft_get_args(int argc, char *argv[], t_vars *vars)
{
	vars->args.philo_count = ft_atoi(argv[1]);
	vars->args.die_time = ft_atoi_ull(argv[2]);
	vars->args.eat_time = ft_atoi_ull(argv[3]);
	vars->args.sleep_time = ft_atoi_ull(argv[4]);
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
		if (!ft_isint(argv[i])
			|| (ft_atoi_ull(argv[i]) == 0 && ft_strcmp(argv[i], "0")
				&& ft_strcmp(argv[i], "-0") && ft_strcmp(argv[i], "+0")))
			return (EXIT_FAILURE);
		i ++;
	}
	ft_get_args(argc, argv, &vars);
	if (vars.args.philo_count < 1 || vars.args.die_time < 1
		|| vars.args.eat_time < 1 || vars.args.sleep_time < 1
		|| vars.args.meals_count < 0)
		return (EXIT_FAILURE);
	philosophers(&vars);
	return (EXIT_SUCCESS);
}
