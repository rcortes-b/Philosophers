#include "../includes/philo.h"

void	*thread_routine(void *arg)
{
	printf("Hola\n");
	for (; *((int*)arg) < 10; (*((int*)arg))++)
		printf("Print this.\n");
	return (NULL);
}

int main(void)
{
	pthread_t	thread1[2];
	pthread_mutex_t	mutex;
	int			value = 0;

	pthread_create(&thread1[0], NULL, thread_routine, &value);
	pthread_create(&thread1[1], NULL, thread_routine, &value);
	pthread_mutex_init(&mutex, NULL);
	pthread_join(thread1[0], NULL);
	printf("This 1 .\n");
	pthread_join(thread1[1], NULL);
	printf("Value: %d\n", value);
	printf("This 2.\n");
	return 0;
}