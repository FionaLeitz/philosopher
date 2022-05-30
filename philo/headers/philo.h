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

typedef struct s_philo
{
	pthread_t		thread;
	int				philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				must_eat;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	*to_write;
	pthread_mutex_t	*is_dead;
	int				*dead;
	pthread_mutex_t	time_mutex;
	struct timeval	*time;
	struct timeval	last_eat;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

typedef struct s_data
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

// struct.c
int	free_struct(t_philo **philo, t_data *data);
int	create_struct(t_data *data, t_philo **philo);
int	get_arg(int argc, char **argv, t_data *data);
// threads.c
int	ft_write(t_philo *philo, char *str, int i);
int	make_thread(t_philo **philo);
// main.c
int	main(int argc, char **argv);

#endif
