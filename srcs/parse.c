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

int	ft_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

static t_philo	**parse_args(t_philo **philo, int argc, char **argv)
{
	t_parse	args;
	int		i;

	args.time_to_die = ft_atoi(argv[0]);
	args.time_to_eat = ft_atoi(argv[1]);
	args.time_to_sleep = ft_atoi(argv[2]);
	if (argc == 6)
		args.num_times_to_eat = ft_atoi(argv[3]);
	i = -1;
	while (philo[++i])
	{
		philo[i]->philo_id = i + 1;
		philo[i]->time_to_die = args.time_to_die;
		philo[i]->time_to_eat = args.time_to_eat;
		philo[i]->time_to_sleep = args.time_to_sleep;
		if (argc == 6)
			philo[i]->num_times_to_eat = args.num_times_to_eat;
	}
	return (philo);
}

static t_philo	**assign_forks(t_philo **philo, int num_of_philo)
{
	pthread_mutex_t	*mutex_fork;
	int				i;

	i = -1;
	while (++i < num_of_philo)
	{
		mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!mutex_fork)
			return (NULL);
		if (i == 0)
		{
			philo[num_of_philo - 1]->right_fork = mutex_fork;
			philo[i]->left_fork = mutex_fork;
		}
		else
		{
			philo[i - 1]->right_fork = mutex_fork;
			philo[i]->left_fork = mutex_fork;
		}
	}
	return (philo);
}

t_philo	**init_philo(t_philo **philo, int argc, char **argv, int num_of_philo)
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
	if (!assign_forks(philo, num_of_philo))
		return (get_freed(philo));
	return (philo);
}
