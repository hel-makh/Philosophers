/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_semaphore.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:23:36 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/17 17:57:28 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_close_semaphores(t_vars *vars)
{
	sem_unlink(FORK_SEM);
	sem_unlink(STATE_SEM);
	sem_unlink(MEALS_SEM);
	sem_close(vars->fork_sem);
	sem_close(vars->state_sem);
	sem_close(vars->meals_sem);
}

int	ft_init_semaphore(sem_t	**sem, char *sem_name, int value)
{
	*sem = sem_open(sem_name, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, value);
	if (*sem == SEM_FAILED)
	{
		sem_unlink(sem_name);
		*sem = sem_open(sem_name, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, value);
		if (*sem == SEM_FAILED)
			return (0);
	}
	return (1);
}

int	ft_init_semaphores(t_vars *vars)
{
	if (!ft_init_semaphore(&vars->fork_sem, FORK_SEM, vars->args.philo_count))
		return (0);
	if (!ft_init_semaphore(&vars->state_sem, STATE_SEM, 1))
	{
		sem_unlink(FORK_SEM);
		sem_close(vars->fork_sem);
		return (0);
	}
	if (!ft_init_semaphore(&vars->meals_sem, MEALS_SEM, 0))
	{
		sem_unlink(FORK_SEM);
		sem_unlink(STATE_SEM);
		sem_close(vars->fork_sem);
		sem_close(vars->state_sem);
		return (0);
	}
	return (1);
}
