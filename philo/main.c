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

static void	*spawn_philosopher(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if ((philo->id + 1) % 2 == 0)
		usleep(100);
	philo->last_meal = ft_get_current_time(philo->vars);
	ft_print_state("is thinking", philo);
	while (!philo->vars->simulation_ended)
	{
		pthread_mutex_lock(&philo->right_fork);
		ft_print_state("has taken a fork", philo);
		pthread_mutex_lock(philo->left_fork);
		ft_print_state("has taken a fork", philo);
		philo->last_meal = ft_get_current_time(philo->vars);
		ft_print_state("is eating", philo);
		philo->meals_count ++;
		ft_msleep(philo->vars->args.eat_time);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		ft_print_state("is sleeping", philo);
		ft_msleep(philo->vars->args.sleep_time);
		ft_print_state("is thinking", philo);
	}
	return (NULL);
}

static int	start_simulation(t_vars *vars, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < vars->args.philo_count)
	{
		if (pthread_create(&philo[i].thread, NULL,
				&spawn_philosopher, (void *)&philo[i]))
			return (EXIT_FAILURE);
	}
	i = 0;
	while (1)
	{
		usleep(100);
		if (philo[i].last_meal + vars->args.die_time
			<= ft_get_current_time(vars))
			return (ft_print_state("died", &philo[i]), EXIT_SUCCESS);
		if (vars->args.meals_count && ft_meals_count_reached(philo))
		{
			vars->simulation_ended = 1;
			return (EXIT_SUCCESS);
		}
		if (++i == vars->args.philo_count)
			i = 0;
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_vars			vars;
	t_philo			*philo;
	struct timeval	time;
	int				exit_status;

	if (argc < 5 || !ft_parse_args(argc, argv, &vars.args))
		return (EXIT_FAILURE);
	gettimeofday(&time, NULL);
	vars.simulation_start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	vars.simulation_ended = 0;
	philo = ft_init_philos(&vars);
	if (!philo)
		return (EXIT_FAILURE);
	if (!ft_init_mutexes(philo))
		return (free(philo), EXIT_FAILURE);
	exit_status = start_simulation(&vars, philo);
	ft_destroy_mutexes(philo);
	philo = ft_free(philo);
	return (exit_status);
}
