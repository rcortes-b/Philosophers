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
		pthread_mutex_lock(philo->died_mutex);
		dead_msg(*philo);
		*philo->is_dead = DEAD_TRIGGER;
		pthread_mutex_unlock(philo->died_mutex);
		return (true);
	}
	return (false);
}

static void	sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->sleep_mutex);
	sleep_msg(*philo);
	pthread_mutex_unlock(philo->sleep_mutex);
	ft_usleep(philo->time_to_sleep);
}

static void	eat_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	fork_msg(*philo, L_FORK);
	pthread_mutex_lock(philo->right_fork);
	fork_msg(*philo, R_FORK);
	eat_msg(*philo);
	pthread_mutex_lock(philo->eat_mutex);
	philo->start = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(philo->eat_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	ft_usleep(philo->time_to_eat);
}

void	*phil_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 != 0)
		ft_usleep(5);
	philo->start = get_time();
	while (*philo->everyone_ate == 0 && !check_death(philo))
	{
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(*philo);
	}
	return (arg);
}

void	*one_phil_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->start = get_time();
	while (!check_death(philo))
	{
		pthread_mutex_lock(&philo->left_fork);
		fork_msg(*philo, L_FORK);
		ft_usleep(philo->time_to_die);
	}
	return (arg);
}
