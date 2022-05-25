/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:07:50 by fleitz            #+#    #+#             */
/*   Updated: 2022/04/20 10:07:59 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include "../libft/headers/ft_printf.h"
# include "../libft/headers/libft.h"

typedef struct	s_philo
{
	pthread_t		thread;
	int				philo;			//	numero du philo
	long int		time_to_die;	//	temps avant de mourir								INUTILE ICI
	long int		time_to_eat;	//	temps pour manger
	long int		time_to_sleep;	//	temps pour dormir
	int				must_eat;		//	nombre de repas minimum								POTENTIELLEMENT UTILE
	pthread_mutex_t	fork;			//	mutex sur sa propre fourchette
	pthread_mutex_t	*next_fork;		//	adresse du mutex de la fourchette du suivant
	pthread_mutex_t	*to_write;		//	adresse du mutex unique d'ecriture
	pthread_mutex_t	*is_dead;		//	mutex sur la variable de mort
	int				*dead;			//	adresse de la variable unique de mort
	pthread_mutex_t	time_mutex;		//	mutex sur la variable de temps last_eat
	struct timeval	*time;			//	temps de reference
	struct timeval	last_eat;		//	temps du dernier repas
	struct s_philo	*next;			//	adresse de la structure du philo suivant
	struct s_philo	*prev;			//	adresse de la structure du philo precedent
}					t_philo;

typedef	struct	s_data
{
	int				nbr_philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				must_eat;
	pthread_mutex_t	is_dead;
	int				dead;
	struct timeval	time;
	pthread_mutex_t	to_write;
}					t_data;

// threads.c
int get_arg(int argc, char **argv, t_data *data);
void	*routine(void *philo);
int	make_thread(t_data *data, t_philo **philo);
// main.c
int	ft_write(t_philo *philo, char *str, int i);
void back_first(t_philo **philo);

#endif
