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

# define DEAD_TRIGGER 1
# define EATEN_TRIGGER 1

enum e_message
{
	L_FORK,
	R_FORK,
	THINK,
	DIED
};

typedef struct s_philo
{
	int				num_of_philos;
	int				philo_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	pthread_t		thrd;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*sleep_mutex;
	pthread_mutex_t	eat;
	pthread_mutex_t	print;
	pthread_mutex_t	sleep;
	int				start;
	int				*is_dead;
	int				times_eaten;
	int				*everyone_ate;
	int				start_time;
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
void	destroy_mutexes(t_philo *philo, int index);

//Parser Utils
int		ft_atoi(char *str);
bool	init_philo(t_philo *philo, int argc, char **argv, int num_of_philo);

//Philo Routine
void	*phil_routine(void *arg);
void	*one_phil_routine(void *arg);
void	print_msg(t_philo *philo, int option);

//Philo Routine Utils
void	ft_usleep(int ms);
int		get_time(void);

#endif
