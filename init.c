/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:56:17 by logkoege          #+#    #+#             */
/*   Updated: 2024/12/17 16:30:17 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_config(t_config *config)
{
	config->count_meal = 0;
	config->num_of_philo = 0;
	config->time_to_die = 0;
	config->time_to_eat = 0;
	config->time_to_sleep = 0;
	config->num_of_meal = 0;
	pthread_mutex_init(&config->printf, NULL);
	pthread_mutex_init(&config->status, NULL);
	pthread_mutex_init(&config->dead, NULL);
	pthread_mutex_init(&config->meal, NULL);
	config = 0;
}

void	init_thread(t_thread **philo, pthread_mutex_t *forks, t_config *config)
{
	int	i;

	i = 0;
	config->start_time = get_time();
	while (i < config->num_of_philo)
	{
		if (pthread_create(&(*philo)[i].thread, NULL, &philo_routine,
			&(*philo)[i]) != 0)
		{
			printf("Error -> thread creation failed for philosopher %d\n", i);
			free_fp(*philo, forks, config);
		}
		i++;
	}
}

int	init_mutex(pthread_mutex_t *forks, int philo)
{
	int	i;

	i = 0;
	while (i < philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			printf("Error -> mutex init failed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philo(t_thread *philo, t_config *config, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < config->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = &forks[i];
		if (i < config->num_of_philo - 1)
			philo[i].right_fork = &forks[(i + 1)];
		else
			philo[i].right_fork = &forks[0];
		philo[i].config = config;
		philo[i].last_meal = 0;
		i++;
	}
	return (0);
}

int	init(t_thread *philo, t_config *config, pthread_mutex_t *forks)
{
	if (init_mutex(forks, config->num_of_philo))
		return (1);
	if (init_philo(philo, config, forks))
		return (1);
	return (0);
}
