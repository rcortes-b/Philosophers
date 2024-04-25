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

static bool	init_mutex(t_philo *philo, int num_of_philo)
{
	int	i;

	i = 0;
	while (i < num_of_philo)
	{
		if (pthread_mutex_init(&philo[i].left_fork, NULL) != 0)
			return (destroy_mutexes(philo, i - 1, 0), false);
		if (pthread_mutex_init(&philo[i].die_mutex, NULL) != 0)
			return (destroy_mutexes(philo, i - 1, 1), false);
		if (pthread_mutex_init(&philo[i].eat_mutex, NULL) != 0)
			return (destroy_mutexes(philo, i - 1, 2), false);
		if (pthread_mutex_init(&philo[i].sleep_mutex, NULL) != 0)
			return (destroy_mutexes(philo, i - 1, 3), false);
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
	int	i;

	i = -1;
	parse_args(&data, argc, argv);
	while (++i < num_of_philo)
	{
		philo[i].start = 0;
		philo[i].num_of_philos = num_of_philo;
		philo[i].philo_id = i + 1;
		philo[i].times_eaten = 0;
		philo[i].time_to_die = data.time_to_die;
		philo[i].time_to_eat = data.time_to_eat;
		philo[i].time_to_sleep = data.time_to_sleep;
		philo[i].num_times_to_eat = data.num_times_to_eat;
	}
	if (!init_mutex(philo, num_of_philo))
		return (free(philo), false);
	return (true);
}
