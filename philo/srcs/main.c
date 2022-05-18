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
	data->dead = 0;
	if (argc == 6)
		data->must_eat = ft_atol(argv[5]);
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*philo2;

	philo2 = philo;
	pthread_mutex_lock(philo2->to_write);
	ft_printf("philo->philo = %d\n", philo2->philo);
	pthread_mutex_unlock(philo2->to_write);
	sleep(1);
	philo2->dead[0] = 1;
	return (NULL);
}

int	make_thread(t_data *data, t_philo **philo)
{
	int	n;

	back_first(philo);
	n = 0;
	while (n < data->nbr_philo)
	{
		if (pthread_create(&(*philo)->thread, NULL, &routine, *philo) != 0)
			return (1);
		*philo = (*philo)->next;
		n++;
//		ft_printf("n = %d\n", n);
	}
	return (0);
}

void	free_struct(t_philo **philo)
{
	t_philo	*tmp;

	back_first(philo);
	while (*philo)
	{
		tmp = *philo;
		*philo = (*philo)->next;
		free(tmp);
	}
}

// int	create_mutex()

int	create_struct(t_data *data, t_philo **philo)
{
	int		i;
	t_philo	*element;
	t_philo	*tmp;

	i = 1;
	tmp = NULL;
	(*philo) = NULL;
	while (i <= data->nbr_philo)
	{
		element = malloc(sizeof(t_philo) * 1);
		if (element == NULL)
		{
			free_struct(philo);
			return (1);
		}
		element->philo = i;
		element->time_to_die = data->time_to_die;
		element->time_to_eat = data->time_to_eat;
		element->time_to_sleep = data->time_to_sleep;
		element->must_eat = data->must_eat;
		element->prev = tmp;
		element->next = NULL;
		element->dead = &data->dead;
		element->to_write = &data->to_write;
		tmp = element;
//		ft_printf("philo numero = %d, die = %d, eat = %d, sleep = %d, must_eat = %d\n", element->philo, element->time_to_die, element->time_to_eat, element->time_to_sleep, element->must_eat);
		if ((*philo) == NULL)
		{
			*philo = element;
		}
		else
		{
			(*philo)->next = element;
			*philo = (*philo)->next;
		}
		i++;
	}
	return (0);
}

void	print_struct(t_philo **philo)
{
	back_first(philo);
	while ((*philo)->next != NULL)
	{
		ft_printf("IN PRINT_STRUCT : philo numero = %d, die = %d, eat = %d, sleep = %d, must_eat = %d\n", (*philo)->philo, (*philo)->time_to_die, (*philo)->time_to_eat, (*philo)->time_to_sleep, (*philo)->must_eat);
		*philo = (*philo)->next;
	}
	ft_printf("IN PRINT_STRUCT : philo numero = %d, die = %d, eat = %d, sleep = %d, must_eat = %d\n", (*philo)->philo, (*philo)->time_to_die, (*philo)->time_to_eat, (*philo)->time_to_sleep, (*philo)->must_eat);
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
	if (make_thread(&data, &philo) == 1)
		ft_printf("Error thread\n");
	while (data.dead == 0)
	{}
	sleep(1);
	free_struct(&philo);
//	pthread_mutex_destroy(&data.to_write);
	return (0);
}