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

static void	eat_philo(t_philo *philo)
{
	eat_msg(*philo);
	pthread_mutex_lock(philo->eat_mutex);
	philo->eating = 1;
	philo->start = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(philo->eat_mutex);
	ft_usleep(philo->time_to_eat);
	philo->eating = 0;
}

static void	sleep_philo(t_philo *philo)
{
	sleep_msg(*philo);
	ft_usleep(philo->time_to_sleep);
}

void	*phil_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 != 0)
		ft_usleep(5);
	philo->eating = 0;
	philo->start = get_time();
	while (*philo->is_dead == 0 && *philo->everyone_ate == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		fork_msg(*philo, L_FORK);
		pthread_mutex_lock(philo->right_fork);
		fork_msg(*philo, R_FORK);
		eat_philo(philo);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
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
	while (*philo->is_dead == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		fork_msg(*philo, L_FORK);
		ft_usleep(philo->time_to_die);
	}
	return (arg);
}
