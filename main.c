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
	philo->last_meal = ft_get_current_time(vars);
	ft_print_state(vars, "is thinking", philo_id + 1, philo->last_meal);
	pthread_mutex_unlock(&vars->mutex);
	while (!vars->simulation_ended)
	{
		if (philo->last_meal + vars->args.die_time < ft_get_current_time(vars))
		{
			ft_print_state(vars, "died", philo_id + 1, ft_get_current_time(vars));
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
