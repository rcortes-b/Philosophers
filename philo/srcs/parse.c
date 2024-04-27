/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:54:13 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/24 11:54:14 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	parse_args(t_parse *data, int argc, char **argv)
{
	data->time_to_die = ft_atoi(argv[0]);
	data->time_to_eat = ft_atoi(argv[1]);
	data->time_to_sleep = ft_atoi(argv[2]);
	if (argc == 6)
		data->num_times_to_eat = ft_atoi(argv[3]);
	else
		data->num_times_to_eat = -1;
}

static bool	init_routines_mutex(t_philo *philo, int num_of_philos)
{
	pthread_mutex_t	eat;
	pthread_mutex_t	die;
	pthread_mutex_t	sleep;
	int				i;

	if (pthread_mutex_init(&die, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&eat, NULL) != 0)
		return (pthread_mutex_destroy(&die), false);
	if (pthread_mutex_init(&sleep, NULL) != 0)
	{
		pthread_mutex_destroy(&eat);
		return (pthread_mutex_destroy(&die), false);
	}
	i = -1;
	while (++i < num_of_philos)
	{
		philo[i].eat_mutex = &eat;
		philo[i].die_mutex = &die;
		philo[i].sleep_mutex = &sleep;
	}
	return (true);
}

static bool	init_mutex(t_philo *philo, int num_of_philo)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
	{
		if (pthread_mutex_init(&philo[i].left_fork, NULL) != 0)
			return (destroy_mutexes(philo, i - 1), false);
		if (i == 0)
			philo[num_of_philo - 1].right_fork = &philo[i].left_fork;
		else
			philo[i - 1].right_fork = &philo[i].left_fork;
		i++;
	}
	return (true);
}

bool	init_philo(t_philo *philo, int argc, char **argv, int num_of_philo)
{
	t_parse	data;
	int		i;

	i = -1;
	parse_args(&data, argc, argv);
	if (!init_routines_mutex(philo, num_of_philo))
		return (free(philo), false);
	if (!init_mutex(philo, num_of_philo))
		return (free(philo), false);
	while (++i < num_of_philo)
	{
		philo[i].num_of_philos = num_of_philo;
		philo[i].philo_id = i + 1;
		philo[i].times_eaten = 0;
		philo[i].time_to_die = data.time_to_die;
		philo[i].time_to_eat = data.time_to_eat;
		philo[i].time_to_sleep = data.time_to_sleep;
		philo[i].num_times_to_eat = data.num_times_to_eat;
	}
	return (true);
}
