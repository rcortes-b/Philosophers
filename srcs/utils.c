/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:11:03 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/22 09:11:04 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	**get_freed(t_philo **philo)
{
	int	i;

	i = -1;
	while (philo[++i])
		free(philo[i]);
	free(philo);
	return (NULL);
}

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
	}
	return (philo);
}

int	check_input(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] != '+' && (argv[i][j] < '0' || argv[i][j] > '9'))
				return (1);
		}
	}
	return (0);
}

void	invalid_input(int error_code)
{
	if (error_code == 1)
		printf("Invalid number of arguments\n");
	else if (error_code == 2)
		printf("Invalid input. It contains more than just numbers\n");
	printf("./pipex <number_of_philosophers> <time_to_die> <time_to_eat> ");
	printf("<time_to_sleep> ");
	printf("<(optional)number_of_times_each_philosopher_must_eat(optional)>\n");
}
