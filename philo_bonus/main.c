/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:32:17 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/14 20:32:17 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

static void	*meals_counter(void *arg)
{
	t_vars	*vars;
	int		counter;

	vars = (t_vars *)arg;
	counter = 0;
	while (counter < vars->args.philo_count)
	{
		sem_wait(vars->meals_sem);
		counter ++;
	}
	while (--counter >= 0)
		kill(vars->pid[counter], SIGKILL);
	return (NULL);
}

static void	*watch_philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		usleep(100);
		if (philo->last_meal + philo->vars->args.die_time
			<= ft_get_current_time(philo->vars))
		{
			ft_print_state("died", philo);
			exit(EXIT_SUCCESS);
		}
	}
	return (NULL);
}

static void	spawn_philosopher(t_philo *philo)
{
	if ((philo->id + 1) % 2 == 0)
		usleep(100);
	philo->last_meal = ft_get_current_time(philo->vars);
	ft_print_state("is thinking", philo);
	if (pthread_create(&philo->thread, NULL, &watch_philosopher, (void *)philo))
		exit(EXIT_FAILURE);
	while (1)
	{
		sem_wait(philo->vars->fork_sem);
		ft_print_state("has taken a fork", philo);
		sem_wait(philo->vars->fork_sem);
		ft_print_state("has taken a fork", philo);
		philo->last_meal = ft_get_current_time(philo->vars);
		ft_print_state("is eating", philo);
		philo->meals_count ++;
		if (philo->vars->args.meals_count
			&& philo->meals_count == philo->vars->args.meals_count)
			sem_post(philo->vars->meals_sem);
		ft_msleep(philo->vars->args.eat_time);
		sem_post(philo->vars->fork_sem);
		sem_post(philo->vars->fork_sem);
		ft_print_state("is sleeping", philo);
		ft_msleep(philo->vars->args.sleep_time);
		ft_print_state("is thinking", philo);
	}
}

static int	start_simulation(t_vars *vars, t_philo *philo)
{
	int		i;

	if (vars->args.meals_count)
		if (pthread_create(&vars->meals_counter, NULL,
				&meals_counter, (void *)vars))
			return (EXIT_FAILURE);
	vars->pid = ft_calloc(vars->args.philo_count, sizeof(pid_t));
	i = 0;
	while (i < vars->args.philo_count)
	{
		vars->pid[i] = fork();
		if (vars->pid[i] == -1)
			return (free(vars->pid), EXIT_FAILURE);
		else if (vars->pid[i] == 0)
			spawn_philosopher(&philo[i]);
		i++;
	}
	waitpid(-1, NULL, 0);
	i = 0;
	while (i < vars->args.philo_count)
		kill(vars->pid[i++], SIGKILL);
	while (waitpid(-1, NULL, 0) != -1)
		;
	return (free(vars->pid), EXIT_SUCCESS);
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
	philo = ft_init_philos(&vars);
	if (!philo)
		return (EXIT_FAILURE);
	if (!ft_init_semaphores(&vars))
		return (free(philo), EXIT_FAILURE);
	exit_status = start_simulation(&vars, philo);
	ft_close_semaphores(&vars);
	philo = ft_free(philo);
	return (exit_status);
}
