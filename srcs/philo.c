/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:06:50 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/22 09:06:51 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//	printf("Hi.\n");

static void	*philo_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	sleep(1);
	printf("Se esta ejecutando el Philo %d\n", philo->philo_id);
	sleep(1);
	
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (philo);
}

static void	dining_philo(t_philo **philo) //, int num_of_philo
{
	int	i;
	int	j;

	i = -1;
	while (philo[++i])
		pthread_create(&philo[i]->thread, NULL, &philo_routine, philo[i]);
	j = -1;
	while (philo[++j])
		pthread_join(philo[j]->thread, NULL);
	i = -1;
	while(philo[++i])
		pthread_detach(philo[i]->thread);
}


int	main(int argc, char **argv)
{
	t_philo	**philo;
	int		num_of_philo;

	if (argc < 5 || argc > 6)
		invalid_input(1);
	else if (check_input(argv))
		invalid_input(2);
	else
	{
		num_of_philo = ft_atoi(argv[1]);
		philo = (t_philo **)malloc(sizeof(t_philo *) * (num_of_philo + 1));
		if (!philo)
			return (0);
		if (!init_philo(philo, argc, &argv[2], num_of_philo))
			return (0);
		dining_philo(philo);
	
		get_freed(philo);
	}
	return (0);
}

	//pthread_t	thread1[2];
	//pthread_mutex_t	mutex;
	//pthread_create(&thread1[0], NULL, thread_routine, &value);

	//pthread_join(thread1[0], NULL);

/*	for (int i = 0; philo[i]; i++)
		printf("Philo %d:\nLeft: %p\nRight: %p\n\n", i + 1, philo[i]->left_fork, philo[i]->right_fork);
	for (int i = 0; philo[i]; i++)
	{
		printf("%d\n", philo[i]->philo_id);
		printf("%d\n", philo[i]->time_to_die);
		printf("%d\n", philo[i]->time_to_eat);
		printf("%d\n", philo[i]->time_to_sleep);
		printf("\n");
	}	
*/