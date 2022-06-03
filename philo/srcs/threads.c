/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:46:39 by fleitz            #+#    #+#             */
/*   Updated: 2022/05/30 14:46:42 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

// special case if a philo is eating
static void	if_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_mutex);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_unlock(&philo->time_mutex);
	usleep(philo->time_to_eat * 1000);
	if (philo->must_eat > -1)
		philo->must_eat--;
	if (philo->must_eat == 0)
	{
		pthread_mutex_lock(philo->is_dead);
		philo->dead[0]--;
		pthread_mutex_unlock(philo->is_dead);
	}
}

// writes states of philos respecting mutexes
int	ft_write(t_philo *philo, char *str, int i)
{
	struct timeval	time2;

	pthread_mutex_lock(philo->to_write);
	pthread_mutex_lock(philo->is_dead);
	if (philo->dead[0] <= 0)
	{
		if (i == 1 || i == 2)
			pthread_mutex_unlock(&philo->fork);
		if (i == 2 || i == 0)
			pthread_mutex_unlock(philo->next_fork);
		pthread_mutex_unlock(philo->is_dead);
		pthread_mutex_unlock(philo->to_write);
		return (1);
	}
	pthread_mutex_unlock(philo->is_dead);
	gettimeofday(&time2, NULL);
	printf("%ld	%d %s\n", ((time2.tv_sec - philo->time->tv_sec) * 1000)
		+ ((time2.tv_usec - philo->time->tv_usec) / 1000), philo->philo, str);
	pthread_mutex_unlock(philo->to_write);
	if (ft_strnstr(str, "eating", ft_strlen(str)) != NULL)
		if_eating(philo);
	return (0);
}

// continuation of routine
static int	routine2(t_philo *philo, pthread_mutex_t *f1, pthread_mutex_t *f2)
{
	pthread_mutex_lock(f1);
	if (ft_write(philo, "has taken a fork", philo->philo % 2) == 1)
		return (1);
	if (f2 == NULL)
	{
		usleep(philo->time_to_die * 1000);
		pthread_mutex_unlock(f1);
		return (1);
	}
	pthread_mutex_lock(f2);
	if (ft_write(philo, "has taken a fork", 2) == 1)
		return (1);
	if (ft_write(philo, "is eating", 2) == 1)
		return (1);
	pthread_mutex_unlock(f2);
	pthread_mutex_unlock(f1);
	return (0);
}

// function where all threads (all philos) will be executed
static void	*routine(void *philo)
{
	t_philo			*philo2;

	philo2 = philo;
	if (philo2->philo % 2 == 0)
		usleep(100);
	while (1)
	{
		if (philo2->philo % 2 == 0)
			if (routine2(philo2, philo2->next_fork, &(philo2->fork)) == 1)
				return (NULL);
		if (philo2->philo % 2 == 1)
			if (routine2(philo2, &(philo2->fork), philo2->next_fork) == 1)
				return (NULL);
		if (ft_write(philo2, "is sleeping", 3) == 1)
			return (NULL);
		usleep(philo2->time_to_sleep * 1000);
		if (ft_write(philo2, "is thinking", 3) == 1)
			return (NULL);
	}
	return (NULL);
}

// creates all the threads
int	make_thread(t_philo **philo)
{
	t_philo	*tmp;

	tmp = *philo;
	while (*philo)
	{
		gettimeofday(&(*philo)->last_eat, NULL);
		if (pthread_create(&(*philo)->thread, NULL, &routine, *philo) != 0)
		{
			*philo = tmp;
			return (1);
		}
		*philo = (*philo)->next;
	}
	*philo = tmp;
	return (0);
}
