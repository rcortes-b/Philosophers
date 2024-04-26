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

/* Porque si es un while (1) no se para el bucle si el monitor checkea el 1 */

static bool check_death(t_philo *philo)
{
	if ((get_time() - philo->start) > philo->time_to_die)
	{
		pthread_mutex_lock(philo->sleep_mutex);
		printf("Bro number %d really died of starve :(\n", philo->philo_id);
		*philo->is_dead = DEAD_TRIGGER;
		pthread_mutex_unlock(philo->sleep_mutex);
		return (true);
	}
	return (false);
}

static void	sleep_msg(t_philo *philo)
{
	pthread_mutex_lock(philo->sleep_mutex);
	printf("Bro number %d is sleepin'\n", philo->philo_id);
	pthread_mutex_unlock(philo->sleep_mutex);
	ft_usleep(philo->time_to_sleep);
}

static void	eat_msg(t_philo *philo)
{
	if (philo->num_of_philos != 1)
	{
		pthread_mutex_lock(philo->eat_mutex);
		printf("Bro number %d is eatin'\n", philo->philo_id);
		philo->times_eaten++;
		pthread_mutex_unlock(philo->eat_mutex);
		ft_usleep(philo->time_to_eat);
	}
}


void	*phil_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 != 0)
		ft_usleep(50);
	philo->start = get_time();
	while (!check_death(philo) && *philo->everyone_ate == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		if (philo->num_of_philos != 1)
		{
			pthread_mutex_lock(philo->right_fork);
			philo->start = get_time();
		}
		printf("Philo %d has taken a fork\n", philo->philo_id);
		eat_msg(philo);
		pthread_mutex_unlock(&philo->left_fork);
		if (philo->num_of_philos != 1)
			pthread_mutex_unlock(philo->right_fork);
		if (*philo->is_dead == DEAD_TRIGGER)
			break ;
		sleep_msg(philo);
		printf("Philo %d is thinkin'\n", philo->philo_id);
	}
	printf("philo id finished: %d\n", philo->philo_id);
	return (arg);
}
