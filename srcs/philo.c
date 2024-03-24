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

/*static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg; //Con esto me he importado toda la estructura por cada philo
}*/

/* Si todo va correctamente, en esta funcion de abajo he asignado la direccion del mutex 0 al fork izquierdo del primero philo
y mutex1 al fork derecho y asi sucesivamente.. *** Si es el ultimo philo le he dado la direccion de mutex0 al fork derecho ***/

//static 

static void	dining_philo(t_philo **philo, int num_of_philo)
{
//	pthread_t		*thread;

//	philo = assign_forks(philo, fork_Mutex);

}

int	main(int argc, char **argv)
{
	t_philo	**philo;
	int		num_of_philo;

	if (argc < 5 || argc > 6)
		invalid_input(1);
	else if (check_input(argv))
		invalid_input(2);
	else
	{
		num_of_philo = ft_atoi(argv[1]);
		philo = (t_philo **)malloc(sizeof(t_philo *) * (num_of_philo + 1));
		if (!philo)
			return (0);
		if (!init_philo(philo, argc, &argv[2], num_of_philo))
			return (0);
		dining_philo(philo, num_of_philo);
	
		get_freed(philo);
	}
	return (0);
}

	//pthread_t	thread1[2];
	//pthread_mutex_t	mutex;
	//pthread_create(&thread1[0], NULL, thread_routine, &value);

	//pthread_join(thread1[0], NULL);

/*	for (int i = 0; philo[i]; i++)
		printf("Philo %d:\nLeft: %p\nRight: %p\n\n", i + 1, philo[i]->left_fork, philo[i]->right_fork);
	for (int i = 0; philo[i]; i++)
	{
		printf("%d\n", philo[i]->philo_id);
		printf("%d\n", philo[i]->time_to_die);
		printf("%d\n", philo[i]->time_to_eat);
		printf("%d\n", philo[i]->time_to_sleep);
		printf("\n");
	}	
*/