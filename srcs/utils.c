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

/* Checker && Error file */

bool	check_input(char **argv)
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
				return (false);
		}
	}
	return (true);
}

void	invalid_input(int error_code)
{
	write(2, "philo error: ", 13);
	if (error_code == 1)
		write(2, "Invalid number of arguments\n", 28);
	else if (error_code == 2)
		write(2, "Invalid input. It contains more than just numbers\n", 50);
	write(2, "./pipex <number_of_philosophers> <time_to_die> <time_to_eat> ", 61);
	write(2, "<time_to_sleep> ", 16);
	write(2, "<(optional)number_of_times_each_philosopher_must_eat(optional)>\n", 64);
}
