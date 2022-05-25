#include "../headers/philo.h"

// norme !
int get_arg(int argc, char **argv, t_data *data)
{
	int	count;
	int	count_arg;

	count_arg = 0;
	while (++count_arg < argc)
	{
		count = 0;
		while (argv[count_arg][count])
		{
			if (ft_isdigit(argv[count_arg][count]) == 0)
				return (1);
			count++;
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

void	*routine(void *philo)
{
	t_philo			*philo2;

	philo2 = philo;
	if (philo2->philo % 2 == 0)
		usleep(100);
	while (1)
	{
		if (philo2->philo % 2 == 0)
		{
			pthread_mutex_lock(philo2->next_fork);
			if (ft_write(philo2, "has taken a fork", 3) == 1)
				return (NULL);
			if (philo2->next_fork == NULL)
			{
				usleep(philo2->time_to_die * 1000);
				pthread_mutex_unlock(philo2->next_fork);
				return (NULL);
			}
			pthread_mutex_lock(&philo2->fork);
			if (ft_write(philo2, "has taken a fork", 4) == 1)
				return (NULL);
			if (ft_write(philo2, "is eating", 4) == 1)
				return (NULL);
			pthread_mutex_unlock(&philo2->fork);
			pthread_mutex_unlock(philo2->next_fork);
		}
		else
		{
			pthread_mutex_lock(&philo2->fork);
			if (ft_write(philo2, "has taken a fork", 1) == 1)
				return (NULL);
			if (philo2->next_fork == NULL)
			{
				usleep(philo2->time_to_die * 1000);
				pthread_mutex_unlock(&philo2->fork);
				return (NULL);
			}
			pthread_mutex_lock(philo2->next_fork);
			if (ft_write(philo2, "has taken a fork", 2) == 1)
				return (NULL);
			if (ft_write(philo2, "is eating", 4) == 1)
				return (NULL);
			pthread_mutex_unlock(philo2->next_fork);
			pthread_mutex_unlock(&philo2->fork);
		}
		if (ft_write(philo2, "is sleeping", 0) == 1)
			return (NULL);
		usleep(philo2->time_to_sleep * 1000);
		if (ft_write(philo2, "is thinking", 0) == 1)
			return (NULL);
	}
	return (NULL);
}

// norme !
int	make_thread(t_data *data, t_philo **philo)
{
	t_philo *tmp;
	(void)data;

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
