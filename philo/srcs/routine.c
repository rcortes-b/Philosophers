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

static void	sleep_msg(t_philo *philo)
{
	pthread_mutex_lock(&philo->sleep_mutex);
	printf("Bro number %d is sleepin'\n", philo->philo_id);
	pthread_mutex_unlock(&philo->sleep_mutex);
	ft_usleep(philo->time_to_sleep);
}

static void	eat_msg(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	printf("Bro number %d is eatin'\n", philo->philo_id);
	pthread_mutex_unlock(&philo->eat_mutex);
	ft_usleep(philo->time_to_eat);
}


void	*phil_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 != 0)
		ft_usleep(100);
	while (*philo->is_dead == 0)
	{
		printf("si o q\n");
		sleep_msg(philo);
		printf("Id: %d\n", philo->philo_id);
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		eat_msg(philo);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		//break ;
	}
	return (arg);
}