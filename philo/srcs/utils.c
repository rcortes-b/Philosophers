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

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		nb = 147483648;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		ft_putchar(nb + 48);
	}
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

//Checks if the input is valid

bool	check_input(char **argv)
{
	int	i;
	int	j;
	int	plus_counter;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		plus_counter = 0;
		while (argv[i][++j])
		{
			if (argv[i][j] == '+')
				plus_counter++;
			if (plus_counter > 1)
				return (false);
			if (argv[i][j] != '+' && (argv[i][j] < '0' || argv[i][j] > '9'))
				return (false);
		}
	}
	return (true);
}

//Throws the error message if the it's an invalid input

void	invalid_input(int error_code)
{
	write(2, "philo error: ", 13);
	if (error_code == 1)
		write(2, "Invalid number of arguments\n", 28);
	else if (error_code == 2)
		write(2, "Invalid input. It contains more than just numbers\n", 50);
	write(2, "./philo <number_of_philosophers>", 32);
	write(2, " <time_to_die> <time_to_eat> ", 29);
	write(2, "<time_to_sleep> ", 16);
	write(2, "<(optional)number_of_times_each", 31);
	write(2, "_philosopher_must_eat(optional)>\n", 33);
}
