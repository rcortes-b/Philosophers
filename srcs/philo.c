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
	t_philo			*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	sleep(1);
	printf("Entra este Philo %d\n", philo->philo_id);
	sleep(1);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	printf("Sale este Philo %d\n", philo->philo_id);
	return (philo);
}

static void	dining_philo(t_philo **philo) //, int num_of_philo
{
	int	i;
	int	j;

	i = -1;
	while (philo[++i])
		pthread_create(&philo[i]->thread, NULL, &philo_routine, philo[i]);
	j = -1;
	while (philo[++j]) // Aqui estoy iniciando el mismo varias veces ya que comparten direccion 
	{
		//pthread_mutex_init(philo[j]->left_fork, NULL);
		pthread_mutex_init(philo[j]->right_fork, NULL);
	}
	j = -1;
	while (philo[++j])
		pthread_join(philo[j]->thread, NULL);
	i = -1;
	while(philo[++i])
		pthread_detach(philo[i]->thread);
	j = -1;
	while (philo[++j]) // Aqui estoy destruyendo algo que ya esta destruido 
	{
		//pthread_mutex_destroy(philo[j]->left_fork);
		pthread_mutex_destroy(philo[j]->right_fork);
	}
}*/

/*static bool	monitorize_threads(t_philo *philo, int num_of_philo)
{
	int	i;


}*/

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		num_of_philo;

	if (argc < 5 || argc > 6)
		invalid_input(1);
	else if (!check_input(argv))
		invalid_input(2);
	else
	{
		num_of_philo = ft_atoi(argv[1]);
		philo = (t_philo *)malloc(sizeof(t_philo) * num_of_philo);
		if (!philo)
			return (0);
		if (!init_philo(philo, argc, &argv[2], num_of_philo))
			return (0);
		



		for (int l = 0; l < num_of_philo; l++)
			pthread_mutex_destroy(&philo[l].left_fork);
		free(philo);
	}
	return (0);
}

/*for (int i = 0; i < num_of_philo; i++)
	{
		printf("philo_id: %d\n", philo[i].philo_id);
		printf("leftfork: %p\n", &philo[i].left_fork);
		printf("rightfork: %p\n", philo[i].right_fork);
		printf("time2die: %d\n", philo[i].time_to_die);
		printf("time2eat: %d\n", philo[i].time_to_eat);
		printf("time2sleep: %d\n", philo[i].time_to_sleep);
		if (argc == 6)
			printf("nbtimes2eat: %d\n", philo[i].num_times_to_eat);
		printf("\n");
	}
	for (int l = 0; l < num_of_philo; l++)
		pthread_mutex_destroy(&philo[l].left_fork);
	free(philo);
*/