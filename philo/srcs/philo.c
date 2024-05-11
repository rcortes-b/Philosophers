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

void	check_to_finish(t_philo *philo);

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
	pthread_mutex_lock(philo[0].died_mutex);
	*philo[0].everyone_ate = EATEN_TRIGGER;
	*philo[0].is_dead = DEAD_TRIGGER;
	has_eaten_msg(*philo);
	pthread_mutex_unlock(philo[0].died_mutex);
	return (true);
}

void	check_to_finish(t_philo *philo)
{
	int	i;

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
				pthread_mutex_lock(philo[0].died_mutex);
				*philo[0].is_dead = 1;
				pthread_mutex_unlock(philo[0].died_mutex);
				dead_msg(&philo[i]);
				return ;
			}
			pthread_mutex_unlock(philo[0].eat_mutex);
		}
		if (times_eaten(philo, philo[0].num_of_philos))
			return ;
	}
}

static bool	monitorize_threads(t_philo *philo, int num_of_philo)
{
	int			has_eaten;
	int			is_dead;
	int			i;

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
	check_to_finish(philo);
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
		if (num_of_philo == 0)
			return (1);
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
