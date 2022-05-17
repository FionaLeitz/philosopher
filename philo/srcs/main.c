#include "../headers/philo.h"

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
	if (argc == 6)
		data->must_eat = ft_atol(argv[5]);
	return (0);
}
/*
void	*routine(void *philo)
{
	t_philo	*philo2;

	philo2 = philo;
	ft_printf("")
	return (NULL);
}

int	make_thread(t_data *data)
{
	int	n;

	data->thread = malloc(sizeof(pthread_t) * data->philo);
	if (data->thread == NULL)
		return (1);
	data->mutex = malloc(sizeof(pthread_mutex_t) * data->philo);
	if (data->mutex == NULL)
		return (1);
	n = 0;
	while (n < data->nbr_philo)
	{
		if (pthread_create(&data->thread[n], NULL, &routine, philo) != 0)
			return (1);
		n++;
	}
	n = 0;
	while (n < data->nbr_philo)
	{
		if (pthread_join(data->thread[n], NULL) != 0)
			return (1);
		n++;
	}
	return (0);
}*/

//int	free_struct()

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
//			free_struct(philo);
			return (1);
		}
		element->philo = i;
		element->time_to_die = data->time_to_die;
		element->time_to_eat = data->time_to_eat;
		element->time_to_sleep = data->time_to_sleep;
		element->must_eat = data->must_eat;
		element->prev = tmp;
		element->next = NULL;
		tmp = element;
		ft_printf("philo numero = %d, die = %d, eat = %d, sleep = %d, must_eat = %d\n", element->philo, element->time_to_die, element->time_to_eat, element->time_to_sleep, element->must_eat);
		if ((*philo) == NULL)
		{
			(*philo) = element;
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
	if (create_struct(&data, &philo) == 1)
		ft_printf("Error malloc\n");
//	philo = philo->prev;
	while (philo->next != NULL)
	{
		ft_printf("IN MAIN : philo numero = %d, die = %d, eat = %d, sleep = %d, must_eat = %d\n", philo->philo, philo->time_to_die, philo->time_to_eat, philo->time_to_sleep, philo->must_eat);
		philo = philo->next;
	}
	ft_printf("IN MAIN : philo numero = %d, die = %d, eat = %d, sleep = %d, must_eat = %d\n", philo->philo, philo->time_to_die, philo->time_to_eat, philo->time_to_sleep, philo->must_eat);
/*	if (make_thread(&data, &res) == 1)
		return (1);*/
	return (0);
}