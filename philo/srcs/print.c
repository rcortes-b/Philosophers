/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:06:50 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/22 09:06:51 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	think_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->print_mutex);
		return ;
	}
	ft_putnbr(get_time() - philo->start_time);
	write(1, " - Philo ", 9);
	ft_putnbr(philo->philo_id);
	write(1, " is \033[1;34mthinking\033[0m\n", 25);
	pthread_mutex_unlock(philo->print_mutex);
}

void	sleep_msg(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->print_mutex);
		return ;
	}
	ft_putnbr(get_time() - philo->start_time);
	write(1, " - Philo ", 9);
	ft_putnbr(philo->philo_id);
	write(1, " is \033[1;31msleeping\033[0m\n", 25);
	pthread_mutex_unlock(philo->print_mutex);
}

void	fork_msg(t_philo *philo, int option)
{
	pthread_mutex_lock(philo->print_mutex);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->print_mutex);
		return ;
	}
	ft_putnbr(get_time() - philo->start_time);
	write(1, " - Philo ", 9);
	ft_putnbr(philo->philo_id);
	if (option == L_FORK)
		write(1, " has taken his \033[1;35mleft fork\033[0m\n", 37);
	else
		write(1, " has taken his \033[1;35mright fork\033[0m\n", 38);
	pthread_mutex_unlock(philo->print_mutex);
}

void	eat_msg(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->print_mutex);
		return ;
	}
	ft_putnbr(get_time() - philo->start_time);
	write(1, " - Philo ", 9);
	ft_putnbr(philo->philo_id);
	write(1, " is \033[1;32meating\033[0m\n", 23);
	pthread_mutex_unlock(philo->print_mutex);
}

void	dead_msg(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	ft_putnbr(get_time() - philo->start_time);
	write(1, " - \033[1;30mPhilo ", 16);
	ft_putnbr(philo->philo_id);
	write(1, " died of starve\033[0m\n", 21);
	pthread_mutex_unlock(philo->print_mutex);
}
