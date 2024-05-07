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

void	*check_to_finish(void *arg);

static bool	init_threads(t_philo *philo, pthread_t monitor, int num_of_philos)
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
		if (pthread_create(&monitor, NULL,
					&check_to_finish, philo) != 0)
			return (destroy_mutexes(philo, num_of_philos), false);
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

	if (philo[0].num_times_to_eat == -1)
		return (false);
	i = -1;
	while (++i < num_of_philo)
	{
		pthread_mutex_lock(philo[0].eat_mutex);
		if (philo[i].num_times_to_eat > philo[i].times_eaten)
		{
			pthread_mutex_unlock(philo[0].eat_mutex);
			return (false);
		}
		pthread_mutex_unlock(philo[0].eat_mutex);
	}
	has_eaten_msg(*philo);
	pthread_mutex_lock(philo[0].died_mutex);
	*philo[0].everyone_ate = EATEN_TRIGGER;
	*philo[0].is_dead = DEAD_TRIGGER;
	pthread_mutex_unlock(philo[0].died_mutex);
	return (true);
}

void	*check_to_finish(void *arg)
{
	t_philo	*philo;
	int	i;

	philo = (t_philo *)arg;
	i = 0;
	while (1)
	{
		i = -1;
		while (++i < philo[0].num_of_philos)
		{
			pthread_mutex_lock(philo[0].eat_mutex);
			if (((get_time() - philo[i].start) >= philo[0].time_to_die)
				&& philo[i].eating == 0)
			{
				pthread_mutex_unlock(philo[0].eat_mutex);
				dead_msg(&philo[i]);
				pthread_mutex_lock(philo[0].died_mutex);
				*philo[0].is_dead = 1;
				pthread_mutex_unlock(philo[0].died_mutex);
				return (arg);
			}
			pthread_mutex_unlock(philo[0].eat_mutex);
		}
		if (times_eaten(philo, philo[0].num_of_philos))
			return (arg);
	}
	return (arg);
}

static bool	monitorize_threads(t_philo *philo, int num_of_philo)
{
	pthread_t	monitor;
	int			i;
	int			is_dead;
	int			has_eaten;

	is_dead = 0;
	has_eaten = 0;
	i = -1;
	while (++i < num_of_philo)
		philo[i].is_dead = &is_dead;
	i = -1;
	while (++i < num_of_philo)
		philo[i].everyone_ate = &has_eaten;
	if (!init_threads(philo, monitor, num_of_philo))
		return (false);
	if (pthread_join(monitor, NULL) != 0)
		return (destroy_mutexes(philo, num_of_philo), false);
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
		if (!monitorize_threads(philo, num_of_philo))
			return (free(philo), 1);
		destroy_mutexes(philo, num_of_philo);
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