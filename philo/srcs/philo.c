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

static bool	init_threads(t_philo *philo, int num_of_philos)
{
	int	i;

	i = -1;
	if (num_of_philos == 1)
	{
		if (pthread_create(&philo[0].thrd, NULL,
				&one_phil_routine, &philo[0]) != 0)
		{
			destroy_mutexes(philo, num_of_philos);
			return (false);
		}
	}
	else
	{
		while (++i < num_of_philos)
		{
			if (pthread_create(&philo[i].thrd, NULL,
					&phil_routine, &philo[i]) != 0)
			{
				destroy_mutexes(philo, num_of_philos);
				return (false);
			}
		}
	}
	return (true);
}

static bool	times_eaten(t_philo *philo, int num_of_philo)
{
	int	i;
	int	counter;

	counter = 0;
	i = -1;
	pthread_mutex_lock(philo[0].eat_mutex);
	while (++i < num_of_philo)
	{
		if (philo[i].num_times_to_eat > philo[i].times_eaten)
			return (false);
		counter++;
	}
	*philo[0].everyone_ate = EATEN_TRIGGER;
	pthread_mutex_unlock(philo[0].eat_mutex);
	printf("Every Philo ");
	printf("has eaten at least %d times!\n", philo[0].num_times_to_eat);
	return (true);
}

static bool	check_to_finish(t_philo *philo, int num_of_philo, int argc)
{
	while (1)
	{
		if (argc == 6)
		{
			if (times_eaten(philo, num_of_philo))
				break ;
		}
		if (*philo[0].is_dead == DEAD_TRIGGER)
			break ;
	}
	return (true);
}

static bool	monitorize_threads(t_philo *philo, int num_of_philo, int argc)
{
	int	i;
	int	is_dead;
	int	has_eaten;

	is_dead = 0;
	has_eaten = 0;
	i = -1;
	while (++i < num_of_philo)
		philo[i].is_dead = &is_dead;
	i = -1;
	while (++i < num_of_philo)
		philo[i].everyone_ate = &has_eaten;
	if (!init_threads(philo, num_of_philo))
		return (false);
	if (check_to_finish(philo, num_of_philo, argc))
		return (true);
	destroy_mutexes(philo, num_of_philo);
	i = -1;
	while (++i < num_of_philo)
	{
		if (pthread_join(philo[i].thrd, NULL) != 0)
			return (destroy_mutexes(philo, num_of_philo), false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		num_of_philo;

	if (argc < 5 || argc > 6)
		return (invalid_input(1), 1);
	else if (!check_input(argv))
		return (invalid_input(2), 1);
	else
	{
		num_of_philo = ft_atoi(argv[1]);
		philo = (t_philo *)malloc(sizeof(t_philo) * num_of_philo);
		if (!philo)
			return (1);
		if (!init_philo(philo, argc, &argv[2], num_of_philo))
			return (free(philo), 1);
		if (!monitorize_threads(philo, num_of_philo, argc))
			return (free(philo), 1);
		free(philo);
	}
	return (0);
}

/*for (int i = 0; i < num_of_philo; i++)
	{
		printf("philo_id: %d\n", philo[i].philo_id);
		printf("leftfork: %p\n", &philo[i].left_fork);
		printf("rightfork: %p\n", philo[i].right_fork);
		printf("time2die: %d\n", philo[i].time_to_die);
		printf("time2eat: %d\n", philo[i].time_to_eat);
		printf("time2sleep: %d\n", philo[i].time_to_sleep);
		if (argc == 6)
			printf("nbtimes2eat: %d\n", philo[i].num_times_to_eat);
		printf("\n");
	}
	for (int l = 0; l < num_of_philo; l++)
		pthread_mutex_destroy(&philo[l].left_fork);
	free(philo);
*/