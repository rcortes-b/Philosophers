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

void	destroy_mutexes(t_philo *philo, int index)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&philo[0].print);
	pthread_mutex_destroy(&philo[0].eat);
	pthread_mutex_destroy(&philo[0].dead);
	while (++i < index)
		pthread_mutex_destroy(&philo[i].left_fork);
}

void	has_eaten_msg(t_philo philo)
{
	pthread_mutex_lock(philo.print_mutex);
	ft_putnbr(get_time() - philo.start_time);
	write(1, " - \033[1;30mEvery Philo has eaten at least ", 42);
	ft_putnbr(philo.num_times_to_eat);
	write(1, " times!\033[0m\n", 13);
	pthread_mutex_unlock(philo.print_mutex);
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

bool	keep_dinner(t_philo philo)
{
	if (*philo.is_dead == 1 || *philo.everyone_ate == 1)
		return (false);
	return (true);
}
