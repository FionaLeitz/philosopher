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
/*
// fills struct data with informations
static t_philo	*set_up(t_data *data, t_philo *tmp, int i)
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
static pthread_mutex_t	*ft_list(t_philo **philo, t_philo *lmt, t_philo **tmp)
{
	pthread_mutex_t	*tmp_fork;
	pthread_mutex_t	*tmp_fork_last;

	tmp_fork = &lmt->fork;
	if ((*philo) == NULL)
	{
		tmp_fork_last = tmp_fork;
		*philo = lmt;
		*tmp = *philo;
	}
	else
	{
		(*philo)->next_fork = tmp_fork;
		(*philo)->next = lmt;
		*philo = (*philo)->next;
	}
	return (tmp_fork_last);
}
*/
// creates philos
/*int	create_struct(t_data *data, t_philo **philo)
{
	int				i;
	t_philo			*element;
	t_philo			*tmp;
	t_philo			*tmp2;
	pthread_mutex_t	*tmp_fork;
	pthread_mutex_t	*tmp_fork_last;

	i = 0;
	tmp2 = NULL;
	(*philo) = NULL;
	tmp_fork = NULL;
	gettimeofday(&data->time, NULL);
	while (++i <= data->nbr_philo)
	{
		element = set_up(data, tmp2, i);
		if (element == NULL)
			return (free_struct(philo, data));
		tmp2 = element;
		if ((*philo) == NULL)
		{
			tmp_fork_last = tmp_fork;
			*philo = element;
			tmp = *philo;
		}
		else
		{
			(*philo)->next_fork = tmp_fork;
			(*philo)->next = element;
			*philo = (*philo)->next;
		}
//		tmp_fork = ft_list(philo, element, &tmp);

	}
	(*philo)->next_fork = tmp_fork_last;
	if (data->nbr_philo == 1)
		(*philo)->next_fork = NULL;
	*philo = tmp;
	return (0);
}*/

pthread_mutex_t	*set_up(t_data *data, t_philo *element, int i, t_philo *tmp)
{
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
	return (&element->fork);
}



int	create_struct(t_data *data, t_philo **philo)
{
	int				i;
	t_philo			*element;
	t_philo			*tmp;
	t_philo			*tmp2;
	pthread_mutex_t	*tmp_fork;
	pthread_mutex_t	*tmp_fork_last;

	i = 0;
	tmp = NULL;
	(*philo) = NULL;
	gettimeofday(&data->time, NULL);
	while (++i <= data->nbr_philo)
	{
		element = malloc(sizeof(t_philo) * 1);
		if (element == NULL)
		{
			free_struct(philo, data);
			return (1);
		}
		tmp_fork = set_up(data, element, i, tmp);
		tmp = element;
		if ((*philo) == NULL)
		{
			tmp_fork_last = tmp_fork;
			*philo = element;
			tmp2 = *philo;
		}
		else
		{
			(*philo)->next_fork = tmp_fork;
			(*philo)->next = element;
			*philo = (*philo)->next;
		}
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
