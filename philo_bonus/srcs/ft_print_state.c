/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-makh <hel-makh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:32:12 by hel-makh          #+#    #+#             */
/*   Updated: 2022/02/16 11:15:15 by hel-makh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_print_state(char *state, t_philo *philo)
{
	sem_wait(philo->vars->state_sem);
	printf("%ld %d %s\n", ft_get_current_time(philo->vars),
		philo->id + 1, state);
	sem_post(philo->vars->state_sem);
}
