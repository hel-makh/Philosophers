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

static void	philo_change_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	ft_print_state("has taken a fork", philo, ft_get_current_time(philo->vars));
	pthread_mutex_lock(philo->left_fork);
	ft_print_state("has taken a fork", philo, ft_get_current_time(philo->vars));
	philo->last_meal = ft_get_current_time(philo->vars);
	ft_print_state("is eating", philo, philo->last_meal);
	philo->meals_count ++;
	usleep(philo->vars->args.eat_time * 1000);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	ft_print_state("is sleeping", philo, ft_get_current_time(philo->vars));
	usleep(philo->vars->args.sleep_time * 1000);
	ft_print_state("is thinking", philo, ft_get_current_time(philo->vars));
}

static void	*spawn_philosopher(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	philo->last_meal = ft_get_current_time(philo->vars);
	ft_print_state("is thinking", philo, philo->last_meal);
	if ((philo->philo_id + 1) % 2 == 0)
		usleep(100);
	while (!philo->vars->simulation_ended)
		philo_change_state(philo);
	return (NULL);
}

static void	*watch_simulation(void *arg)
{
	t_philo		*philo;
	int			philo_count;
	int			i;

	philo = (t_philo *)arg;
	philo_count = philo[0].vars->args.philo_count;
	i = 0;
	while (1)
	{
		if (philo[i].last_meal + philo[i].vars->args.die_time
			< ft_get_current_time(philo[i].vars))
		{
			ft_print_state("died", &philo[i],
				ft_get_current_time(philo[i].vars));
			break ;
		}
		if (philo[0].vars->args.meals_count && ft_meals_count_reached(philo))
		{
			philo->vars->simulation_ended = 1;
			break ;
		}
		if (++i == philo_count)
			i = 0;
	}
	return (NULL);
}

static int	start_simulation(t_vars *vars, t_philo *philo)
{
	int	i;

	if (pthread_create(&vars->watch_simulation, NULL, &watch_simulation, (void *)philo))
		return (EXIT_FAILURE);
	i = 0;
	while (i < vars->args.philo_count)
	{
		if (pthread_create(&philo[i].thread, NULL,
				&spawn_philosopher, (void *)&philo[i]))
			return (EXIT_FAILURE);
		i ++;
	}
	if (pthread_join(vars->watch_simulation, NULL))
		return (EXIT_FAILURE);
	i = 0;
	while (i < vars->args.philo_count)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (EXIT_FAILURE);
		i ++;
	}
	return (EXIT_SUCCESS);
}

static t_philo	*ft_init_philo(t_vars *vars)
{
	t_philo	*philo;
	int		i;

	philo = ft_calloc(vars->args.philo_count, sizeof(t_philo));
	if (!philo)
		return (NULL);
	i = 0;
	while (i < vars->args.philo_count)
	{
		philo[i].philo_id = i;
		philo[i].vars = vars;
		i ++;
	}
	return (philo);
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
	philo = ft_init_philo(&vars);
	if (!philo)
		return (EXIT_FAILURE);
	if (!ft_init_mutexes(philo))
		return (free(philo), EXIT_FAILURE);
	exit_status = start_simulation(&vars, philo);
	ft_destroy_mutexes(philo);
	philo = ft_free(philo);
	return (exit_status);
}
