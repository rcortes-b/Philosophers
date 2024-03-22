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
			if (argv[i][j] < '0' || argv[i][j] > '9')
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
