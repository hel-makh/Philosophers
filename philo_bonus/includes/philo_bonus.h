/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:21:12 by hel-makh          #+#    #+#             */
/*   Updated: 2022/01/31 19:21:12 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <limits.h>

# define FORK_SEM "fork"
# define STATE_SEM "state"
# define QUEUE_SEM "queue"

typedef struct s_args {
	int			philo_count;
	long		die_time;
	long		eat_time;
	long		sleep_time;
	int			meals_count;
}	t_args;

typedef struct s_vars {
	t_args		args;
	sem_t		*fork_sem;
	sem_t		*state_sem;
	sem_t		*queue_sem;
	long		simulation_start;
}	t_vars;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	long		last_meal;
	int			meals_count;
	t_vars		*vars;
}	t_philo;

void	*ft_calloc(size_t count, size_t size);
void	*ft_free(void *ptr);
void	*ft_free_2d(void **ptr);
void	*ft_free_3d(void ***ptr);
long	ft_get_current_time(t_vars *vars);
void	ft_msleep(long sleeptime);

int		ft_parse_args(int argc, char *argv[], t_args *args);
int		ft_init_semaphores(t_vars *vars);
void	ft_close_semaphores(t_vars *vars);
void	ft_print_state(char *state, t_philo *philo);

#endif