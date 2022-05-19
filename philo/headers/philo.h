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
	long int		time_to_die;	//	temps avant de mourir
	long int		time_to_eat;	//	temps pour manger
	long int		time_to_sleep;	//	temps pour dormir
	int				must_eat;		//	nombre de repas minimum
	pthread_mutex_t	fork;			//	mutex sur sa propre fourchette
	pthread_mutex_t	*next_fork;		//	adresse du mutex de la fourchette du suivant
	pthread_mutex_t	*to_write;		//	adresse du mutex unique d'ecriture
	int				*dead;			//	adresse de la variable unique de mort
	struct timeval	*time;
	struct timeval	time2;
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
	int				dead;
	struct timeval	time;
	pthread_mutex_t	to_write;
}					t_data;

#endif
