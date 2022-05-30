#include "../headers/philo.h"

// norme !
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

// norme !
int	routine2(t_philo *philo, pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	pthread_mutex_lock(fork1);
	if (ft_write(philo, "has taken a fork", philo->philo % 2) == 1)
		return (1);
	if (fork2 == NULL)
	{
		usleep(philo->time_to_die * 1000);
		pthread_mutex_unlock(fork1);
		return (1);
	}
	pthread_mutex_lock(fork2);
	if (ft_write(philo, "has taken a fork", 2) == 1)
		return (1);
	if (ft_write(philo, "is eating", 2) == 1)
		return (1);
	pthread_mutex_unlock(fork2);
	pthread_mutex_unlock(fork1);
	return (0);
}

// norme !
void	*routine(void *philo)
{
	t_philo			*philo2;

	philo2 = philo;
	if (philo2->philo % 2 == 0)
		usleep(100);
	while (1)
	{
		if (philo2->philo % 2 == 0)
			if (routine2(philo2, philo2->next_fork, &philo2->fork) == 1)
				return (NULL);
		if (philo2->philo % 2 == 1)
			if (routine2(philo2, &philo2->fork, philo2->next_fork) == 1)
				return (NULL);
		if (ft_write(philo2, "is sleeping", 3) == 1)
			return (NULL);
		usleep(philo2->time_to_sleep * 1000);
		if (ft_write(philo2, "is thinking", 3) == 1)
			return (NULL);
	}
	return (NULL);
}

// norme !
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
