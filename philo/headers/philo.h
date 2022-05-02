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
/*
typedef struct	s_philo
{
	int		philo;
	t_philo	*next;
	t_philo	*prev;
}		t_philo;
*/
typedef	struct	s_data
{
	int				nbr_philo;
	long int		die;
	long int		eat;
	long int		sleep;
	long int		must_eat;
	int				*philo;
	pthread_t		*thread;
	pthread_mutex_t	*mutex;
}					t_data;

#endif
