/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleitz <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:07:30 by fleitz            #+#    #+#             */
/*   Updated: 2022/04/20 10:07:33 by fleitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philo.h"

// les threads partagent la meme memoire

// fonction appelee par pthread, fonction qui commence un thread
/*void	*routine(void *mails)
{
	int	*mails2;
	int	i;

	mails2 = mails;
	i = 0;
	while (i++ < 100000)		// le probleme, un thread lit dans la memoire, recupere l'info (disons 42),
		mails2[0]++;			// se met en pause pour x raison, l'autre thread continue (disons jusque 65), 
	return (NULL);				// puis le premier thread reprend (42), incremente ce qu'il a, et remplace l'information dans la memoire
}								// et on repart en arriere (43)

void	*routine2(void *x)
{
	int	*x2;

	x2 = x;
	sleep(2);
	printf("x = %d\n", x2[0]);
	return (NULL);
}*/

void	*routine(void *test)
{
	t_test	*test2;
	int	i;

	test2 = test;
	i = 0;
	while (i++ < 10000000)
	{
		pthread_mutex_lock(&test2->mutex);
		test2->mails++;
		pthread_mutex_unlock(&test2->mutex);
	}
	return (NULL);
}

// pthread = type de variable, remplie par la fonction pthread_create
// qui permet d'identifier le thread
// pthread_join = permet d'attendre la fin d'un thread identifie
// pthread_create et pthread_join retourne un int, 0 si tout va bien
int	main()
{
	pthread_t	t1;
	pthread_t	t2;
	t_test		test;

	test.mails = 0;
	pthread_mutex_init(&test.mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, &test) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, &test) != 0)
		return (1);
	if (pthread_join(t1, NULL) != 0)
		return (1);
	if (pthread_join(t2, NULL) != 0)
		return (1);
	pthread_mutex_destroy(&test.mutex);
	printf("Number of mails : %d\n", test.mails);
	return (0);
}

