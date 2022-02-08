/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_sleeping.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:16:00 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/05 18:16:00 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_get_fork_to_drop(t_vars *vars, int philo_id, int *starving_id)
{
	int	right_philo_id;
	int	left_philo_id;

	right_philo_id = philo_id + 1;
	if (right_philo_id >= vars->args.philo_count)
		right_philo_id = 0;
	left_philo_id = philo_id - 1;
	if (left_philo_id < 0)
		left_philo_id = vars->args.philo_count - 1;
	if (vars->args.philo_count % 2 != 0
		|| right_philo_id < left_philo_id)
	{
		*starving_id = right_philo_id;
		return ('R');
	}
	else
	{
		*starving_id = left_philo_id;
		return ('L');
	}
	return (0);
}

static void	ft_drop_forks(t_vars *vars, int philo_id)
{
	t_philo	*philo;
	t_philo	*starving_philo;
	int		starving_philo_id;
	int		fork_to_drop;

	philo = &vars->philo[philo_id];
	fork_to_drop = ft_get_fork_to_drop(vars, philo_id, &starving_philo_id);
	starving_philo = &vars->philo[starving_philo_id];
	pthread_mutex_lock(&vars->mutex);
	if (fork_to_drop == 'R')
		philo->right_hand = 0;
	else if (fork_to_drop == 'L')
		philo->left_hand = 0;
	pthread_mutex_unlock(&vars->mutex);
	while (!starving_philo->right_hand || !starving_philo->left_hand)
		;
	pthread_mutex_lock(&vars->mutex);
	if (fork_to_drop == 'R')
		philo->left_hand = 0;
	else if (fork_to_drop == 'L')
		philo->right_hand = 0;
	pthread_mutex_unlock(&vars->mutex);
}

void	ft_start_sleeping(t_vars *vars, int philo_id)
{
	ft_drop_forks(vars, philo_id);
	pthread_mutex_lock(&vars->mutex);
	ft_print_state(vars, "is sleeping", philo_id + 1,
		ft_get_current_time(vars));
	pthread_mutex_unlock(&vars->mutex);
	// ft_msleep(vars->args.sleep_time);
	usleep(vars->args.sleep_time * 1000);
	pthread_mutex_lock(&vars->mutex);
	ft_print_state(vars, "is thinking", philo_id + 1,
		ft_get_current_time(vars));
	pthread_mutex_unlock(&vars->mutex);
}
