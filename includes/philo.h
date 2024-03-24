/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:27:04 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/22 09:27:04 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				philo_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	pthread_mutex_t	*left_fork; //if philo is 0, fork left is 4
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_parse
{
	int	philo_id;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_times_to_eat;
}	t_parse;

//Errors && Checkers
t_philo	**get_freed(t_philo **philo);
void	invalid_input(int error_code);
int		check_input(char **argv);

//Parser Utils
int		ft_atoi(char *str);
t_philo	**init_philo(t_philo **philo, int argc, char **argv, int num_of_philo);

#endif

//t_philo	**assign_forks(t_philo **philo, int num_of_philo);