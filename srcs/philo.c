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

/* How routine will works */

/* Como cojones puedo bloquear los forks ??? */

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg; //Con esto me he importado toda la estructura por cada philo
}

static t_philo	**init_philo(t_philo **philo, int argc, char **argv, int num_of_philo)
{
	int	i;

	i = -1;
	while (++i < num_of_philo)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[i])
			return (get_freed(philo));
	}
	philo[i] = NULL;
	philo = parse_args(philo, argc, argv);
	return (philo);
}

static void	dining_philo(t_philo **philo, int num_of_philo)
{
	pthread_t		thread[num_of_philo];
	pthread_mutex_t	forkMutex[num_of_philo]; //No se si hace falta tantos mutes, pero si quizas declarar unos forks
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
		philo = (t_philo **)malloc(sizeof(t_philo *) * num_of_philo);
		if (!philo)
			return (0);
		if (!init_philo(philo, argc, &argv[2], num_of_philo))
			return (0);
		dining_philo(philo, num_of_philo);
		
		
		get_freed(philo);
	}
	return (0);
}

	//pthread_t	thread1[2];
	//pthread_mutex_t	mutex;
	//pthread_create(&thread1[0], NULL, thread_routine, &value);

	//pthread_join(thread1[0], NULL);

/*	for (int i = 0; philo[i]; i++)
	{
		printf("%d\n", philo[i]->philo_id);
		printf("%d\n", philo[i]->time_to_die);
		printf("%d\n", philo[i]->time_to_eat);
		printf("%d\n", philo[i]->time_to_sleep);
		printf("\n");
	}	*/