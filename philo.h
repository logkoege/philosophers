/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:56:10 by logkoege          #+#    #+#             */
/*   Updated: 2024/12/18 15:23:50 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

// Struct config
typedef struct s_config
{
	long long		start_time;		// Debut de la simulation
	long long		time_to_die;	// Temps avant de mourir
	int				time_to_eat;	// Temps pour manger
	int				time_to_sleep;	// Temps pour dormir
	int				num_of_meal;	// Nombre de repas
	int				num_of_philo;	// Nombre de philo
	int				stop;			// Bool pour la mort des philo
	int				count_meal;		// Compteur de repas
	int				free_forks;		// Bool pour savoir si forks a etais malloc
	int				free_philo;		// Bool pour savoir si philo a etais malloc
	pthread_mutex_t	printf;			// Mutex pour les printf
	pthread_mutex_t	meal;			// Mutex pour les repas
	pthread_mutex_t	status;			// Mutex pour la mort
	pthread_mutex_t	dead;			// Mutex pour compter les repas
}	t_config;

// Struct philo
typedef struct s_thread
{
	long long		last_meal;	// Dernier repas mangé (temps)
	int				id;			// Identifiant du philosophe
	pthread_t		thread;		// Thread du philosophe
	pthread_mutex_t	*left_fork;		// Fourchette gauche
	pthread_mutex_t	*right_fork;	// Fourchette droite
	t_config		*config;		// Pointeur vers la config
}	t_thread;

// init.c
void		init_config(t_config *config);
void		init_thread(t_thread **philo, pthread_mutex_t *forks,
				t_config *config);
int			init_mutex(pthread_mutex_t *forks, int philo);
int			init_philo(t_thread *philo, t_config *config,
				pthread_mutex_t *forks);
int			init(t_thread *philo, t_config *config, pthread_mutex_t *forks);

// utils.c
int			alloc(t_thread **philo, pthread_mutex_t **forks, t_config *config);
int			ft_atoi(char *str);
void		free_fp(t_thread *philo, pthread_mutex_t *forks, t_config *config);
int			printf_lock(t_thread *philo, char *msg);
int			nb_of_meal(t_thread *philo);

// utils_2.c
long long	get_time(void);
void		ft_usleep(long long time);
void		while_life(t_thread **philo, t_config *config);
int			is_alive(t_thread *philo);
int			philo_is_alive(t_thread *philo);

// routine.c
void		*philo_routine(void *arg);
int			philo_thinking(t_thread *philo);
int			philo_eating(t_thread *philo);
int			fork_muting(t_thread *philo);
int			philo_sleeping(t_thread *philo);

// parsing.c
int			if_1_philo(t_config *config);
int			pars_arg(int argc, char **argv, t_config *config);
int			end_it(t_thread **philo, pthread_mutex_t *forks);
int			for_odd(t_thread *philo);

// the_end.c
int			meal_count(t_thread *philo);
int			fork_muting_1(t_thread *philo);
int			fork_muting_2(t_thread *philo);
int			for_odd_1(t_thread *philo);
int			for_odd_2(t_thread *philo);

#endif