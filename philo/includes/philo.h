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
# include <stdbool.h>

#define DEAD_TRIGGER 1

typedef struct s_philo
{
	int				philo_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	pthread_t		thrd;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	sleep_mutex;
	struct timeval	tv_start;
	struct timeval	tv_end;
	int				*is_dead;
	int				times_eaten;
}	t_philo;

typedef struct s_parse
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_times_to_eat;
}	t_parse;

//Errors && Checkers
void	invalid_input(int error_code);
bool	check_input(char **argv);
void	destroy_mutexes(t_philo *philo, int index, int trigger);

//Parser Utils
int		ft_atoi(char *str);
bool	init_philo(t_philo *philo, int argc, char **argv, int num_of_philo);

//Philo Routine
void	*phil_routine(void *arg);

void 	ft_usleep(int ms);

#endif
