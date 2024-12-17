/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:56:03 by logkoege          #+#    #+#             */
/*   Updated: 2024/12/17 16:21:07 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char**argv)
{
	t_config		config;
	t_thread		*philo;
	pthread_mutex_t	*forks;

	init_config(&config);
	if (pars_arg(argc, argv, &config) || alloc(&philo, &forks, &config))
		return (1);
	if (init(philo, &config, forks))
	{
		free_fp(philo, forks, &config);
		return (1);
	}
	init_thread(&philo, forks, &config);
	while_life(&philo, &config);
	end_it(&philo, forks);
	return (0);
}
