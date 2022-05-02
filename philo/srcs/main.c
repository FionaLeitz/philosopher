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
				return (0);
			count++;
		}
		count_arg++;
	}
	data->nbr_philo = ft_atoi(argv[1]);
	data->die = ft_atol(argv[2]);
	data->eat = ft_atol(argv[3]);
	data->sleep = ft_atol(argv[4]);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atol(argv[5]);
	return (1);
}

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
}

int main(int argc, char **argv)
{
	t_data	data;
	t_philo	philo;

	if (!(argc == 5 || argc == 6))
	{
		ft_printf("Too few arguments\n");
		return (1);
	}
	if (get_arg(argc, argv, &data) == 0)
	{
		ft_printf("Wrong arguments\n");
		return (1);
	}
//	ft_printf("philo = %d, die = %d, eat = %d, sleep = %d, must_eat = %d\n", data.philo, data.die, data.eat, data.sleep, data.must_eat);
	if (make_thread(&data, &res) == 1)
		return (1);
	return (0);
}