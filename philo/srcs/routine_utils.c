/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:10:11 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/22 11:10:12 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_msg(t_philo *philo, int option)
{
	pthread_mutex_lock(philo->print_mutex);
	if (*philo->everyone_ate || *philo->is_dead)
		return ;
	if (option == L_FORK)
	{
		printf("%d - Philo N°%d has taken his \033[1;35mleft fork\033[0m\n",
			get_time() - philo->start_time, philo->philo_id);
	}
	else if (option == R_FORK)
	{
		printf("%d - Philo N°%d has taken his \033[1;35mright fork\033[0m\n",
			get_time() - philo->start_time, philo->philo_id);
	}
	else if (option == THINK)
	{
		printf("%d - Philo N°%d is \033[1;34mthinking\033[0m\n",
			get_time() - philo->start_time, philo->philo_id);
	}
	if (option == DIED)
	{
		printf("%d - Philo N°%d \033[1;30mdied of starve\033[0m\n",
			get_time() - philo->start_time, philo->philo_id);
	}
	pthread_mutex_unlock(philo->print_mutex);
}

int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (write(2, "gettimeofday error\n", 19), 0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	int	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(500);
}
