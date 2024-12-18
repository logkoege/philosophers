/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:02:48 by logkoege          #+#    #+#             */
/*   Updated: 2024/12/18 14:23:56 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc(t_thread **philo, pthread_mutex_t **forks, t_config *config)
{
	(*philo) = malloc(sizeof(t_thread) * config->num_of_philo);
	if (!philo)
	{
		printf("Error -> malloc failed\n");
		return (1);
	}
	config->free_philo = 1;
	(*forks) = malloc(sizeof(pthread_mutex_t) * config->num_of_philo);
	if (!forks)
	{
		printf("Error -> malloc failed\n");
		free_fp(*philo, *forks, config);
		return (1);
	}
	config->free_forks = 1;
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	nombre;
	int	signe;

	signe = 1;
	nombre = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-')
	{
		signe = -signe;
		i++;
	}
	while (str[i] && (str[i] <= '9' && str[i] >= '0'))
	{
		nombre = nombre * 10 + (str[i] - '0');
		i++;
	}
	if (str[i])
		return (-1);
	return (nombre * signe);
}

void	free_fp(t_thread *philo, pthread_mutex_t *forks, t_config *config)
{
	if (config->free_philo)
		free(philo);
	if (config->free_forks)
		free(forks);
}

int	printf_lock(t_thread *philo, char *msg)
{
	pthread_mutex_lock(&philo->config->printf);
	pthread_mutex_lock(&(philo->config->dead));
	if (philo->config->stop == 1)
	{
		pthread_mutex_unlock(&philo->config->printf);
		pthread_mutex_unlock(&(philo->config->dead));
		return (1);
	}
	pthread_mutex_unlock(&(philo->config->dead));
	pthread_mutex_lock(&philo->config->meal);
	if (philo->config->num_of_meal != 0)
	{
		if (philo->config->count_meal / philo->config->num_of_philo
			== philo->config->num_of_meal)
		{
			pthread_mutex_unlock(&philo->config->printf);
			pthread_mutex_unlock(&philo->config->meal);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->config->meal);
	printf("%lld %d %s", get_time()
		- philo->config->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->config->printf);
	return (0);
}

int	nb_of_meal(t_thread *philo)
{
	if (philo->config->count_meal / philo->config->num_of_philo
		== philo->config->num_of_meal)
	{
		pthread_mutex_unlock(&philo->config->meal);
		return (1);
	}
	philo->config->count_meal++;
	return (0);
}
