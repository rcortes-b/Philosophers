/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:10:11 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/22 11:10:12 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	check_death(t_philo *philo)
{
	if ((get_time() - philo->start) >= philo->time_to_die)
	{
		pthread_mutex_lock(philo->sleep_mutex);
		printf("Philo N°%d died of starve\n", philo->philo_id);
		*philo->is_dead = DEAD_TRIGGER;
		pthread_mutex_unlock(philo->sleep_mutex);
		return (true);
	}
	return (false);
}

static void	sleep_msg(t_philo *philo)
{
	pthread_mutex_lock(philo->sleep_mutex);
	printf("Philo N°%d is sleeping\n", philo->philo_id);
	pthread_mutex_unlock(philo->sleep_mutex);
	ft_usleep(philo->time_to_sleep);
}

static void	eat_msg(t_philo *philo)
{
	pthread_mutex_lock(philo->eat_mutex);
	printf("Philo N°%d is eating\n", philo->philo_id);
	philo->times_eaten++;
	pthread_mutex_unlock(philo->eat_mutex);
	ft_usleep(philo->time_to_eat);
}

void	*phil_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 != 0)
		ft_usleep(50);
	philo->start = get_time();
	while (*philo->everyone_ate == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		printf("Philo N°%d has taken his left fork\n", philo->philo_id);
		pthread_mutex_lock(philo->right_fork);
		printf("Philo N°%d has taken his right fork\n", philo->philo_id);
		if (check_death(philo))
			break ;
		philo->start = get_time();
		eat_msg(philo);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		sleep_msg(philo);
		printf("Philo N°%d is thinking\n", philo->philo_id);
	}
	return (arg);
}

void	*one_phil_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->start = get_time();
	while (!check_death(philo) && *philo->everyone_ate == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		printf("Philo N°%d has taken his left fork\n", philo->philo_id);
		pthread_mutex_unlock(&philo->left_fork);
		printf("Philo N°%d ", philo->philo_id);
		printf("has left his left fork in the table\n");
		sleep_msg(philo);
		printf("Philo N°%d is thinking\n", philo->philo_id);
	}
	return (arg);
}
