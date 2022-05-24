#include "../headers/philo.h"

void back_first(t_philo **philo)
{
	if (*philo == NULL)
		return ;
	while ((*philo)->prev)
		*philo = (*philo)->prev;
}

int get_arg(int argc, char **argv, t_data *data)
{
	int	count;
	int	count_arg;

	count_arg = 1;
	while (count_arg < argc)
	{
		count = 0;
		while (argv[count_arg][count])
		{
			if (ft_isdigit(argv[count_arg][count]) == 0)
				return (1);
			count++;
		}
		count_arg++;
	}
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->must_eat = -1;
	data->dead = data->nbr_philo;
	pthread_mutex_init(&data->is_dead, NULL);
	if (argc == 6)
		data->must_eat = ft_atol(argv[5]);
	return (0);
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
		if (philo->must_eat > -1)
			philo->must_eat--;
		if (philo->must_eat == 0)
		{
			pthread_mutex_lock(philo->is_dead);
			philo->dead[0]--;
			pthread_mutex_unlock(philo->is_dead);
		}
		pthread_mutex_lock(&philo->time_mutex);
		gettimeofday(&philo->last_eat, NULL);
		pthread_mutex_unlock(&philo->time_mutex);
	}
	return (0);
}

void	*routine1(void *philo)
{
	t_philo		*philo2;

	philo2 = philo;
	if (philo2->philo % 2 == 0)
		usleep(philo2->time_to_eat * 100);
	while (1)
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
		if (ft_write(philo2, "is eating", 2) == 1)
			return (NULL);
		usleep(philo2->time_to_eat * 1000);
		pthread_mutex_unlock(philo2->next_fork);
		pthread_mutex_unlock(&philo2->fork);
		if (ft_write(philo2, "is sleeping", 0) == 1)
			return (NULL);
		usleep(philo2->time_to_sleep * 1000);
		if (ft_write(philo2, "is thinking", 0) == 1)
			return (NULL);
	}
	return (NULL);
}

void	*routine2(void *philo)
{
	t_philo		*philo2;

	philo2 = philo;
	if (philo2->philo % 2 == 0)
		usleep(/*philo2->time_to_eat * */100);
	while (1)
	{
		pthread_mutex_lock(philo2->next_fork);
		if (ft_write(philo2, "has taken a fork", 3) == 1)
			return (NULL);
		if (philo2->next_fork == NULL)
		{
			usleep(philo2->time_to_die * 1000);
			pthread_mutex_unlock(&philo2->fork);
			return (NULL);
		}
		pthread_mutex_lock(&philo2->fork);
		if (ft_write(philo2, "has taken a fork", 4) == 1)
			return (NULL);
		if (ft_write(philo2, "is eating", 4) == 1)
			return (NULL);
		usleep(philo2->time_to_eat * 1000);
		pthread_mutex_unlock(&philo2->fork);
		pthread_mutex_unlock(philo2->next_fork);
		if (ft_write(philo2, "is sleeping", 0) == 1)
			return (NULL);
		usleep(philo2->time_to_sleep * 1000);
		if (ft_write(philo2, "is thinking", 0) == 1)
			return (NULL);
	}
	return (NULL);
}

int	make_thread(t_data *data, t_philo **philo)
{
	int	n;
	t_philo *tmp;

	back_first(philo);
	tmp = *philo;
	n = 0;
	while (n < data->nbr_philo)
	{
		gettimeofday(&(*philo)->last_eat, NULL);
		if (n % 2 == 0)
		{
			if (pthread_create(&(*philo)->thread, NULL, &routine2, *philo) != 0)
				return (1);
		}
		else
		{
			if (pthread_create(&(*philo)->thread, NULL, &routine1, *philo) != 0)
				return (1);
		}
		*philo = (*philo)->next;
		n++;
	}
	*philo = tmp;
	return (0);
}

void	free_struct(t_philo **philo)
{
	t_philo	*tmp;

	back_first(philo);
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
			free_struct(philo);
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
	return (0);
}

int	ft_dead(t_philo	**philo)
{
	struct timeval	time2;

	while ((*philo)->next)
	{
		pthread_mutex_lock(&(*philo)->time_mutex);
		gettimeofday(&time2, NULL);
		if (((time2.tv_sec - (*philo)->last_eat.tv_sec) * 1000) + ((time2.tv_usec - (*philo)->last_eat.tv_usec) / 1000) >= (*philo)->time_to_die)
		{
			if (ft_write(*philo, "is dead", 0) == 1)
			{
				pthread_mutex_unlock(&(*philo)->time_mutex);
				return (1);
			}
			pthread_mutex_lock((*philo)->is_dead);
			(*philo)->dead[0] = 0;
			pthread_mutex_unlock((*philo)->is_dead);
			pthread_mutex_unlock(&(*philo)->time_mutex);
			return (1);
		}
		pthread_mutex_unlock(&(*philo)->time_mutex);
		*philo = (*philo)->next;
	}
	gettimeofday(&time2, NULL);
	pthread_mutex_lock(&(*philo)->time_mutex);
	if (((time2.tv_sec - (*philo)->last_eat.tv_sec) * 1000) + ((time2.tv_usec - (*philo)->last_eat.tv_usec) / 1000) >= (*philo)->time_to_die)
	{
		if (ft_write(*philo, "is dead", 0) == 1)
		{
			pthread_mutex_unlock(&(*philo)->time_mutex);
			return (1);
		}
		pthread_mutex_lock((*philo)->is_dead);
		(*philo)->dead[0] = 0;
		pthread_mutex_unlock((*philo)->is_dead);
		pthread_mutex_unlock(&(*philo)->time_mutex);
		return (1);
	}
	pthread_mutex_unlock(&(*philo)->time_mutex);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (!(argc == 5 || argc == 6))
	{
		ft_printf("Wrong number of arguments\n");
		return (1);
	}
	if (get_arg(argc, argv, &data) == 1)
	{
		ft_printf("Wrong arguments\n");
		return (1);
	}
	pthread_mutex_init(&data.to_write, NULL);
	if (create_struct(&data, &philo) == 1)
		ft_printf("Error malloc\n");
/*	back_first(&philo);
	while (philo->next){
		printf("philo %d : adresse de fork = %p\n", philo->philo, &philo->fork);
		philo = philo->next;
	}
	printf("philo %d : adresse de fork = %p\n", philo->philo, &philo->fork);*/
	back_first(&philo);
	if (make_thread(&data, &philo) == 1)
		ft_printf("Error threads\n");
//	while (data.dead != 0)
	while (1)
	{
		pthread_mutex_lock(&data.is_dead);
		if (data.dead == 0)
		{
			pthread_mutex_unlock(&data.is_dead);
			break ;
		}
		pthread_mutex_unlock(&data.is_dead);
		back_first(&philo);
		ft_dead(&philo);
	}
	back_first(&philo);
	while (philo->next)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
	}
	pthread_join(philo->thread, NULL);
	pthread_mutex_destroy(&data.to_write);
	pthread_mutex_destroy(&data.is_dead);
	free_struct(&philo);
	return (0);
}