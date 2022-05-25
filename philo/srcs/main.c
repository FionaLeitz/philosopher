#include "../headers/philo.h"

void back_first(t_philo **philo)
{
	if (*philo == NULL)
		return ;
	while ((*philo)->prev)
		*philo = (*philo)->prev;
}

int	ft_write(t_philo *philo, char *str, int i)
{
	struct timeval	time2;
	
	pthread_mutex_lock(philo->to_write);
	pthread_mutex_lock(philo->is_dead);
	if (philo->dead[0] == 0)
	{
		if (i == 1 || i == 2)
			pthread_mutex_unlock(&philo->fork);
		if (i == 2)
			pthread_mutex_unlock(philo->next_fork);
		if (i == 3 || i == 4)
			pthread_mutex_unlock(philo->next_fork);
		if (i == 4)
			pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->is_dead);
		pthread_mutex_unlock(philo->to_write);
		return (1);
	}
	pthread_mutex_unlock(philo->is_dead);
	gettimeofday(&time2, NULL);
	printf("%ld	%d %s\n", ((time2.tv_sec - philo->time->tv_sec) * 1000) + ((time2.tv_usec - philo->time->tv_usec) / 1000), philo->philo, str);
	pthread_mutex_unlock(philo->to_write);
	if (ft_strnstr(str, "eating", ft_strlen(str)) != NULL)
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
	return (0);
}

void	free_struct(t_philo **philo, t_data data)
{
	t_philo	*tmp;

	pthread_mutex_destroy(&data.to_write);
	pthread_mutex_destroy(&data.is_dead);
	while (*philo)
	{
		pthread_mutex_destroy(&(*philo)->fork);
		pthread_mutex_destroy(&(*philo)->time_mutex);
		tmp = *philo;
		*philo = (*philo)->next;
		free(tmp);
	}
}

int	create_struct(t_data *data, t_philo **philo)
{
	int				i;
	t_philo			*element;
	t_philo			*tmp;
	t_philo			*tmp2;
	pthread_mutex_t	*tmp_fork;
	pthread_mutex_t	*tmp_fork_last;

	i = 1;
	tmp = NULL;
	(*philo) = NULL;
	gettimeofday(&data->time, NULL);
	while (i <= data->nbr_philo)
	{
		element = malloc(sizeof(t_philo) * 1);
		if (element == NULL)
		{
			free_struct(philo, *data);
			return (1);
		}
		pthread_mutex_init(&element->fork, NULL);
		pthread_mutex_init(&element->time_mutex, NULL);
		tmp_fork = &element->fork;
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
		i++;
	}
	(*philo)->next_fork = tmp_fork_last;
	if (data->nbr_philo == 1)
		(*philo)->next_fork = NULL;
	*philo = tmp2;
	return (0);
}

int	ft_dead(t_philo	**philo)
{
	struct timeval	time2;
	t_philo			*tmp;

	tmp = *philo;
	while (*philo)
	{
		pthread_mutex_lock(&(*philo)->time_mutex);
		gettimeofday(&time2, NULL);
		if (((time2.tv_sec - (*philo)->last_eat.tv_sec) * 1000) + ((time2.tv_usec - (*philo)->last_eat.tv_usec) / 1000) >= (*philo)->time_to_die)
		{
			if (ft_write(*philo, "is dead", 0) == 1)
			{
				pthread_mutex_unlock(&(*philo)->time_mutex);
				*philo = tmp;
				return (1);
			}
			pthread_mutex_lock((*philo)->is_dead);
			(*philo)->dead[0] = 0;
			pthread_mutex_unlock((*philo)->is_dead);
			pthread_mutex_unlock(&(*philo)->time_mutex);
			*philo = tmp;
			return (1);
		}
		pthread_mutex_unlock(&(*philo)->time_mutex);
		*philo = (*philo)->next;
	}
	*philo = tmp;
	return (0);
}

int	if_dead(t_data *data)
{
	pthread_mutex_lock(&data->is_dead);
	if (data->dead == 0)
	{
		pthread_mutex_unlock(&data->is_dead);
		return (1);
	}
	pthread_mutex_unlock(&data->is_dead);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	t_philo	*tmp;

	if (!(argc == 5 || argc == 6))
		return (ft_printf("Wrong number of arguments\n"));
	if (get_arg(argc, argv, &data) == 1)
		return (ft_printf("Wrong arguments\n"));
	if (create_struct(&data, &philo) == 1)
		return (ft_printf("Error malloc\n"));
	tmp = philo;
	if (make_thread(&data, &philo) == 1)
	{
		free_struct(&philo, data);
		return (ft_printf("Error threads\n"));
	}
	while (if_dead(&data) == 0)
		ft_dead(&philo);
	while (philo)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
	}
	philo = tmp;
	free_struct(&philo, data);
	return (0);
}