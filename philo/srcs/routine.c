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
		pthread_mutex_lock(philo->eat_mutex);
		pthread_mutex_lock(philo->sleep_mutex);
		print_msg(philo, DIED);
		*philo->is_dead = DEAD_TRIGGER;
		pthread_mutex_unlock(philo->eat_mutex);
		pthread_mutex_unlock(philo->sleep_mutex);
		pthread_mutex_unlock(philo->print_mutex);
		return (true);
	}
	return (false);
}

static void	sleep_msg(t_philo *philo)
{
	pthread_mutex_lock(philo->sleep_mutex);
	pthread_mutex_lock(philo->print_mutex);
	if (*philo->everyone_ate || *philo->is_dead)
		return ;
	printf("%d - Philo N°%d is \033[1;31msleeping\033[0m\n",
		get_time() - philo->start_time, philo->philo_id);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_unlock(philo->sleep_mutex);
	ft_usleep(philo->time_to_sleep);
}

static void	eat_msg(t_philo *philo)
{
	pthread_mutex_lock(philo->eat_mutex);
	pthread_mutex_lock(philo->print_mutex);
	if (*philo->everyone_ate || *philo->is_dead)
		return ;
	printf("%d - Philo N°%d is \033[1;32meating\033[0m\n",
		get_time() - philo->start_time, philo->philo_id);
	philo->times_eaten++;
	pthread_mutex_unlock(philo->print_mutex);
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
	while (*philo->everyone_ate == 0 && *philo->is_dead == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		print_msg(philo, L_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, R_FORK);
		if (check_death(philo))
			break ;
		philo->start = get_time();
		eat_msg(philo);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		sleep_msg(philo);
		print_msg(philo, THINK);
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
		print_msg(philo, L_FORK);
		ft_usleep(philo->time_to_die);
	}
	return (arg);
}
