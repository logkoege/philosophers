/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:44:53 by logkoege          #+#    #+#             */
/*   Updated: 2024/12/12 19:58:40 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	the_end_of_for_odd(t_thread *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (printf_lock(philo, "has taken a fork\n") == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	if (is_alive(philo) == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	if (printf_lock(philo, "is eating\n") == 1)
		return (1);
	return (0);
}

int	the_end_of_fork_muting(t_thread *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (printf_lock(philo, "has taken a fork\n") == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		return (1);
	}
	if (is_alive(philo) == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	if (printf_lock(philo, "is eating\n") == 1)
		return (1);
	return (0);
}
