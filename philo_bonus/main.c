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

static void	*watch_philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->last_meal + philo->vars->args.die_time
			<= ft_get_current_time(philo->vars))
		{
			ft_print_state("died", philo);
			exit(EXIT_SUCCESS);
		}
		if (philo->vars->args.meals_count && ft_meals_count_reached(philo))
		{
			philo->vars->simulation_ended = 1;
			exit(EXIT_SUCCESS);
		}
	}
	return (NULL);
}

static int	spawn_philosopher(t_philo *philo)
{
	philo->last_meal = ft_get_current_time(philo->vars);
	ft_print_state("is thinking", philo);
	if ((philo->id + 1) % 2 == 0)
		usleep(10);
	if (pthread_create(&philo->thread, NULL,
			&watch_philosopher, (void *)philo))
		return (EXIT_FAILURE);
	while (!philo->vars->simulation_ended)
	{
		sem_wait(philo->vars->semaphore);
		ft_print_state("has taken a fork", philo);
		sem_wait(philo->vars->semaphore);
		ft_print_state("has taken a fork", philo);
		philo->last_meal = ft_get_current_time(philo->vars);
		ft_print_state("is eating", philo);
		philo->meals_count ++;
		ft_msleep(philo->vars->args.eat_time);
		sem_post(philo->vars->semaphore);
		sem_post(philo->vars->semaphore);
		ft_print_state("is sleeping", philo);
		ft_msleep(philo->vars->args.sleep_time);
		ft_print_state("is thinking", philo);
	}
	return (EXIT_SUCCESS);
}

static int	start_simulation(t_vars *vars, t_philo *philo)
{
	pid_t	*pid;
	int		i;

	pid = ft_calloc(vars->args.philo_count, sizeof(pid_t));
	i = 0;
	while (i < vars->args.philo_count)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (EXIT_FAILURE);
		else if (pid[i] == 0)
			return (spawn_philosopher(&philo[i]));
		i ++;
	}
	waitpid(-1, NULL, 0);
	i = 0;
	while (i < vars->args.philo_count)
		kill(pid[i++], SIGKILL);
	while (waitpid(-1, NULL, 0) != -1)
		;
	pid = ft_free(pid);
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
		philo[i].id = i;
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
	vars.semaphore = sem_open(SEM, O_CREAT, 0644, vars.args.philo_count);
	if (vars.semaphore == SEM_FAILED)
		return (EXIT_FAILURE);
	exit_status = start_simulation(&vars, philo);
	sem_unlink(SEM);
	sem_close(vars.semaphore);
	philo = ft_free(philo);
	return (exit_status);
}
