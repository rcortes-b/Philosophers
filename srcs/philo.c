/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 09:06:50 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/22 09:06:51 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*void	*thread_routine(void *arg)
{
	
}*/

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		invalid_input(1);
	else if (check_input(argv))
		invalid_input(2);
	else
	{

	}


	//pthread_t	thread1[2];
	//pthread_mutex_t	mutex;
	//pthread_create(&thread1[0], NULL, thread_routine, &value);

	//pthread_join(thread1[0], NULL);
	return (0);
}
