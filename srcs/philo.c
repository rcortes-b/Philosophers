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

static t_philo	**init_philo(t_philo **philo, int argc, char **argv)
{
	int	i;
	int	num_of_philo;

	num_of_philo = ft_atoi(argv[1]);
	i = -1;
	while (++i < num_of_philo)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!philo[i])
			return (get_freed(philo));
	}
	philo[i] = NULL;
	philo = parse_args(philo, argc, &argv[2]);
	return (philo);
}

/*void	*thread_routine(void *arg)
{
	
}*/

int	main(int argc, char **argv)
{
	t_philo	**philo;

	if (argc < 5 || argc > 6)
		invalid_input(1);
	else if (check_input(argv))
		invalid_input(2);
	else
	{
		philo = (t_philo **)malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
		if (!philo)
			return (0);
		if (!init_philo(philo, argc, argv))
			return (0);
		
		
		
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