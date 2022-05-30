/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:46:30 by fleitz            #+#    #+#             */
/*   Updated: 2022/05/30 14:46:33 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

// writes death if no one died already
static void	set_up_death(t_philo *philo)
{
	if (ft_write(philo, "is dead", 3) == 1)
	{
		pthread_mutex_unlock(&philo->time_mutex);
		return ;
	}
	pthread_mutex_lock(philo->is_dead);
	philo->dead[0] = 0;
	pthread_mutex_unlock(philo->is_dead);
	pthread_mutex_unlock(&philo->time_mutex);
	return ;
}

// checks if a philo ate too long ago
static int	check_death(t_philo	**philo)
{
	struct timeval	time2;
	t_philo			*tmp;

	tmp = *philo;
	while (*philo)
	{
		pthread_mutex_lock(&(*philo)->time_mutex);
		gettimeofday(&time2, NULL);
		if (((time2.tv_sec - (*philo)->last_eat.tv_sec) * 1000)
			+ ((time2.tv_usec - (*philo)->last_eat.tv_usec) / 1000)
			>= (*philo)->time_to_die)
		{
			set_up_death(*philo);
			*philo = tmp;
			return (1);
		}
		pthread_mutex_unlock(&(*philo)->time_mutex);
		*philo = (*philo)->next;
	}
	*philo = tmp;
	return (0);
}

// checks if a philo already died (or ate enough)
static int	if_dead(t_data *data)
{
	pthread_mutex_lock(&data->is_dead);
	if (data->dead <= 0)
	{
		pthread_mutex_unlock(&data->is_dead);
		return (1);
	}
	pthread_mutex_unlock(&data->is_dead);
	return (0);
}

// checks if arguments are ok and if struct created correctly
static int	check_error(int argc, char **argv, t_data *data, t_philo **philo)
{
	if (!(argc == 5 || argc == 6))
	{
		ft_printf("Wrong number of arguments\n");
		return (1);
	}
	if (get_arg(argc, argv, data) == 1)
	{
		ft_printf("Wrong arguments\n");
		return (1);
	}
	if (create_struct(data, philo) == 1)
	{
		ft_printf("Error malloc\n");
		return (1);
	}
	return (0);
}

// main
int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	t_philo	*tmp;

	if (check_error(argc, argv, &data, &philo) == 1)
		return (1);
	tmp = philo;
	if (make_thread(&philo) == 1)
	{
		free_struct(&philo, &data);
		return (ft_printf("Error threads\n"));
	}
	while (if_dead(&data) == 0)
		check_death(&philo);
	while (philo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
	}
	philo = tmp;
	free_struct(&philo, &data);
	return (0);
}
