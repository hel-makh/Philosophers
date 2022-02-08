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
// #include "srcs/ft_get_current_time.c"

// #include "srcs/ft_is_fork_surrounded.c"
// #include "srcs/ft_meals_count_reached.c"
// #include "srcs/ft_start_eating.c"
// #include "srcs/ft_start_sleeping.c"
// #include "srcs/ft_return_error.c"

// static void	philo_change_state(t_vars *vars, int philo_id)
// {
// 	t_philo		*philo;

// 	philo = &vars->philo[philo_id];
// 	pthread_mutex_lock(&philo->right_fork);
// 	ft_print_state("has taken a fork", philo_id + 1,
// 		ft_get_current_time(vars), vars);
// 	pthread_mutex_lock(philo->left_fork);
// 	ft_print_state("has taken a fork", philo_id + 1,
// 		ft_get_current_time(vars), vars);
// 	philo->last_meal = ft_get_current_time(vars);
// 	ft_print_state("is eating", philo_id + 1, philo->last_meal, vars);
// 	usleep(vars->args.eat_time * 1000);
// 	pthread_mutex_unlock(&philo->right_fork);
// 	pthread_mutex_unlock(philo->left_fork);
// 	ft_print_state("is sleeping", philo_id + 1,
// 		ft_get_current_time(vars), vars);
// 	usleep(vars->args.sleep_time * 1000);
// 	ft_print_state("is thinking", philo_id + 1,
// 		ft_get_current_time(vars), vars);
// }

static void	*start_simulation(void *arg)
{
	t_vars		*vars;
	t_philo		*philo;
	int			philo_id;

	vars = (t_vars *)arg;
	philo_id = vars->philo_id;
	philo = &vars->philo[philo_id];
	philo->last_meal = ft_get_current_time(vars);
	ft_print_state("is thinking", philo_id + 1, philo->last_meal, vars);
	vars->philo[vars->philo_id].philo_id = philo_id + 1;
	while (!vars->simulation_ended)
	{
		if (philo->last_meal + vars->args.die_time < ft_get_current_time(vars))
		{
			ft_print_state("died", philo_id + 1, ft_get_current_time(vars), vars);
			break ;
		}
		if (ft_is_fork_surrounded(vars, philo_id))
			if (ft_start_eating(vars, philo_id) == -1)
				break ;
	}
	// while (!vars->simulation_ended)
	// 	philo_change_state(vars, philo_id);
	return (EXIT_SUCCESS);
}

static int	philosophers(t_vars *vars)
{
	vars->philo_id = 0;
	while (vars->philo_id < vars->args.philo_count)
	{
		if (pthread_create(&vars->philo[vars->philo_id].thread, NULL,
				&start_simulation, (void *)vars))
			return (free(vars->philo), EXIT_FAILURE);
		while (!vars->philo[vars->philo_id].philo_id)
			;
		vars->philo_id ++;
	}
	vars->philo_id = 0;
	while (vars->philo_id < vars->args.philo_count)
	{
		if (pthread_join(vars->philo[vars->philo_id].thread, NULL))
			return (free(vars->philo), EXIT_FAILURE);
		vars->philo_id ++;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_vars			vars;
	struct timeval	time;
	int				exit_status;

	if (argc < 5 || !ft_parse_args(argc, argv, &vars))
		return (EXIT_FAILURE);
	gettimeofday(&time, NULL);
	vars.simulation_start = time.tv_sec * 1000000;
	vars.simulation_start += time.tv_usec / 1000;
	vars.simulation_ended = 0;
	vars.philo = ft_calloc(vars.args.philo_count, sizeof(t_philo));
	if (!vars.philo)
		return (EXIT_FAILURE);
	if (!ft_init_mutexes(&vars))
		return (free(vars.philo), EXIT_FAILURE);
	exit_status = philosophers(&vars);
	ft_destroy_mutexes(&vars);
	vars.philo = ft_free(vars.philo);
	return (exit_status);
}
