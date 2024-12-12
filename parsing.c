/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:07:21 by logkoege          #+#    #+#             */
/*   Updated: 2024/12/12 18:41:55 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	if_1_philo(t_config *config)
{
	if (config->num_of_philo == 1)
	{
		printf("0 1 is thinking\n");
		printf("0 1 as taken a fork\n");
		ft_usleep(config->time_to_die);
		printf("%lld 1 is dead\n", config->time_to_die);
		return (1);
	}
	return (0);
}

int	pars_arg(int argc, char **argv, t_config *config)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error -> invalid number of arguments (must be 4 or 5)\n");
		return (1);
	}
	config->num_of_philo = ft_atoi(argv[1]);
	config->time_to_die = ft_atoi(argv[2]);
	config->time_to_eat = ft_atoi(argv[3]);
	config->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		config->num_of_meal = ft_atoi(argv[5]);
	if (config->num_of_philo <= 0 || config->time_to_die <= 0
		||config->time_to_eat <= 0 || config->time_to_sleep <= 0
		|| (argc == 6 && config->num_of_meal <= 0))
	{
		printf("Error -> invalid argument value (must be > 0)\n");
		return (1);
	}
	if (if_1_philo(config) == 1)
		return (1);
	return (0);
}

int	end_it(t_thread **philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < (*philo)->config->num_of_philo)
	{
		pthread_join((*philo)[i].thread, NULL);
		pthread_mutex_destroy((*philo)->left_fork);
		pthread_mutex_destroy((*philo)->right_fork);
		i++;
	}
	pthread_mutex_destroy(&(**philo).config->printf);
	pthread_mutex_destroy(&(**philo).config->status);
	pthread_mutex_destroy(&(**philo).config->dead);
	pthread_mutex_destroy(&(**philo).config->meal);
	free_fp((*philo), forks, (*philo)->config);
	return (0);
}
