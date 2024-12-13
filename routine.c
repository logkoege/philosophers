/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:10:03 by logkoege          #+#    #+#             */
/*   Updated: 2024/12/13 15:56:57 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_thread	*philo;

	philo = (t_thread *) arg;
	if (philo->id % 2 == 0)
		usleep((philo->config->time_to_eat * 1000) / 2);
	while (1)
	{
		if (philo_thinking(philo) == 1)
			return (NULL);
		if (philo_eating(philo) == 1)
			return (NULL);
		if (philo_sleeping(philo) == 1)
			return (NULL);
	}
	return (NULL);
}

int	philo_thinking(t_thread *philo)
{
	if (is_alive(philo) == 1)
		return (1);
	if (printf_lock(philo, "is thinking\n") == 1)
		return (1);
	return (0);
}

int	philo_eating(t_thread *philo)
{
	if (is_alive(philo) == 1)
		return (1);
	if (fork_muting(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->config->status);
	philo->last_meal = get_time() - philo->config->start_time;
	pthread_mutex_unlock(&philo->config->status);
	pthread_mutex_lock(&philo->config->meal);
	if (philo->config->num_of_meal != 0)
	{
		if (nb_of_meal(philo) == 1)
		{
			pthread_mutex_unlock(&philo->config->meal);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->config->meal);
	ft_usleep(philo->config->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	fork_muting(t_thread *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (printf_lock(philo, "has taken a fork\n") == 1)
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
		if (is_alive(philo) == 1)
		{
			pthread_mutex_unlock(philo->left_fork);
			return (1);
		}
		// if (the_end_of_fork_muting(philo) == 1)
		// 	return (1);
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
	if (for_odd(philo) == 1)
		return (1);
	return (0);
}

int	philo_sleeping(t_thread *philo)
{
	if (is_alive(philo) == 1)
		return (1);
	if (printf_lock(philo, "is sleeping\n") == 1)
		return (1);
	ft_usleep(philo->config->time_to_sleep);
	return (0);
}
