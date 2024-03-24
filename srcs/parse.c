/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 11:54:13 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/24 11:54:14 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

/* El primer philosopher tendra el left fork como 0 y el derecho como 1, el philo1 tendra el izquierdo como 1 y derecho como 2, asi hasta que el siguiente sea NULL, en ese caso el derecho sera el 0*/

t_philo	**parse_args(t_philo **philo, int argc, char **argv)
{
	t_parse	args;
	int		i;

	args.time_to_die = ft_atoi(argv[0]);
	args.time_to_eat = ft_atoi(argv[1]);
	args.time_to_sleep = ft_atoi(argv[2]);
	if (argc == 6)
		args.num_times_to_eat = ft_atoi(argv[3]);
	i = -1;
	while (philo[++i])
	{
		philo[i]->philo_id = i + 1;
		philo[i]->time_to_die = args.time_to_die;
		philo[i]->time_to_eat = args.time_to_eat;
		philo[i]->time_to_sleep = args.time_to_sleep;
		if (argc == 6)
			philo[i]->num_times_to_eat = args.num_times_to_eat;
		philo[i]->left_fork = i;
		if (philo[i + 1])
			philo[i]->right_fork = i + 1;
		else
			philo[i]->right_fork = 0;
	}
	return (philo);
}