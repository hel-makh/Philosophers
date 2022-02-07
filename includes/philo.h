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

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef unsigned long long	t_timestamp;

typedef struct s_args {
	int				philo_count;
	t_timestamp		die_time;
	t_timestamp		eat_time;
	t_timestamp		sleep_time;
	int				meals_count;
}	t_args;

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	int				right_hand;
	int				left_hand;
	t_timestamp		last_meal;
	int				meals_count;
}	t_philo;

typedef struct s_vars {
	t_args			args;
	t_philo			*philo;
	int				philo_id;
	pthread_mutex_t	mutex;
}	t_vars;

int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isint(const char *str);
int			ft_atoi(const char *str);
t_timestamp	ft_atoi_ull(const char *str);
void		*ft_calloc(size_t count, size_t size);
void		*ft_free(void *ptr);
void		*ft_free_2d(void **ptr);
void		*ft_free_3d(void ***ptr);
t_timestamp	ft_get_timestamp(void);
void		ft_usleep(t_timestamp sleeptime);

int			ft_is_fork_surrounded(t_vars *vars, int philo_id);
int			ft_meals_count_reached(t_vars vars);
int			ft_start_eating(t_vars *vars, int philo_id);
void		ft_start_sleeping(t_vars *vars, int philo_id);
int			ft_return_error(
				int status, t_vars *vars, int unlock_mutex, int destroy_mutex
				);

#endif