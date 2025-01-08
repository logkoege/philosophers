/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:05:31 by logkoege          #+#    #+#             */
/*   Updated: 2025/01/08 16:24:45 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error -> gettimeofday()\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long long time)
{
	usleep(time * 1000);
}

void	while_life(t_thread **philo, t_config *config)
{
	int	j;

	while (1)
	{
		j = -1;
		while (++j < config->num_of_philo)
		{
			if (is_alive(&(*philo)[j]))
				return ;
			pthread_mutex_lock(&(*philo)->config->meal);
			if ((*philo)->config->num_of_meal != 0)
			{
				if (meal_count(*philo) == 0)
				{
					pthread_mutex_unlock(&(*philo)->config->meal);
					return ;
				}
			}
			pthread_mutex_unlock(&(*philo)->config->meal);
		}
	}
}

int	is_alive(t_thread *philo)
{
	pthread_mutex_lock(&philo->config->dead);
	if (philo->config->stop == 1)
	{
		pthread_mutex_unlock(&(philo->config->dead));
		return (1);
	}
	pthread_mutex_unlock(&(philo->config->dead));
	if (philo_is_alive(philo) == 1)
	{
		printf_lock(philo, "died\n");
		pthread_mutex_lock(&(philo->config->dead));
		philo->config->stop = 1;
		pthread_mutex_unlock(&(philo->config->dead));
		return (1);
	}
	return (0);
}

int	philo_is_alive(t_thread *philo)
{
	pthread_mutex_lock(&philo->config->status);
	if (get_time() - philo->config->start_time
		- philo->last_meal > philo->config->time_to_die + 5)
	{
		pthread_mutex_unlock(&philo->config->status);
		return (1);
	}
	pthread_mutex_unlock(&philo->config->status);
	return (0);
}
