/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:24:23 by fleitz            #+#    #+#             */
/*   Updated: 2022/05/30 15:24:26 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

// frees all the list
int	free_struct(t_philo **philo, t_data *data)
{
	t_philo	*tmp;

	pthread_mutex_destroy(&data->to_write);
	pthread_mutex_destroy(&data->is_dead);
	while ((*philo)->prev)
		(*philo) = (*philo)->prev;
	while (*philo)
	{
		pthread_mutex_destroy(&(*philo)->fork);
		pthread_mutex_destroy(&(*philo)->time_mutex);
		tmp = *philo;
		*philo = (*philo)->next;
		free(tmp);
	}
	return (1);
}

// fills struct data with informations
t_philo	*set_up(t_data *data, int i, t_philo *tmp)
{
	t_philo	*element;

	element = malloc(sizeof(t_philo) * 1);
	if (element == NULL)
		return (NULL);
	pthread_mutex_init(&element->fork, NULL);
	pthread_mutex_init(&element->time_mutex, NULL);
	element->philo = i;
	element->time_to_die = data->time_to_die;
	element->time_to_eat = data->time_to_eat;
	element->time_to_sleep = data->time_to_sleep;
	element->must_eat = data->must_eat;
	element->prev = tmp;
	element->next = NULL;
	element->is_dead = &data->is_dead;
	element->dead = &data->dead;
	element->to_write = &data->to_write;
	element->time = &data->time;
	return (element);
}

// puts philos in a list
int	create_struct(t_data *data, t_philo **philo)
{
	int				i;
	t_philo			*tmp2;
	pthread_mutex_t	*tmp_fork_last;

	i = 1;
	gettimeofday(&data->time, NULL);
	(*philo) = set_up(data, 1, NULL);
	if (*philo == NULL)
		return (1);
	tmp2 = *philo;
	tmp_fork_last = &(*philo)->fork;
	while (++i <= data->nbr_philo)
	{
		(*philo)->next = set_up(data, i, *philo);
		if ((*philo)->next == NULL)
			return (1);
		(*philo)->next_fork = &(*philo)->next->fork;
		*philo = (*philo)->next;
	}
	(*philo)->next_fork = tmp_fork_last;
	if (data->nbr_philo == 1)
		(*philo)->next_fork = NULL;
	*philo = tmp2;
	return (0);
}

// gets arguments in a usable format
int	get_arg(int argc, char **argv, t_data *data)
{
	int	count;
	int	count_arg;

	count_arg = 0;
	while (++count_arg < argc)
	{
		count = -1;
		while (argv[count_arg][++count])
		{
			if (ft_isdigit(argv[count_arg][count]) == 0)
				return (1);
		}
	}
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->must_eat = -1;
	data->dead = data->nbr_philo;
	pthread_mutex_init(&data->is_dead, NULL);
	pthread_mutex_init(&data->to_write, NULL);
	if (argc == 6)
		data->must_eat = ft_atol(argv[5]);
	return (0);
}
