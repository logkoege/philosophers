/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:44:53 by logkoege          #+#    #+#             */
/*   Updated: 2024/12/18 17:32:46 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_muting_1(t_thread *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->config->meal);
	if (philo->config->num_of_meal != 0)
	{
		if (philo->config->count_meal
			/ philo->config->num_of_philo
			== philo->config->num_of_meal)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(&philo->config->meal);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->config->meal);
	if (printf_lock(philo, "has taken a fork\n") == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	fork_muting_2(t_thread *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (is_alive(philo) == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->config->meal);
	if (philo->config->num_of_meal != 0)
	{
		if (philo->config->count_meal
			/ philo->config->num_of_philo
			== philo->config->num_of_meal)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(&philo->config->meal);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->config->meal);
	return (0);
}

int	meal_count(t_thread *philo)
{
	if ((philo)->config->count_meal
		/ (philo)->config->num_of_philo
		== (philo)->config->num_of_meal)
		return (0);
	else
		return (1);
}
