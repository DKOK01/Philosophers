#include "philo.h"

int n = 0;

void *philosopher_routine()
{
	int i = 0;
	while (i < 10000000)
	{
		n++;
		i++;
	}
	return (NULL);
}

int main(void)
{
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;

    pthread_create(&thread1, NULL, &philosopher_routine, NULL);
    pthread_create(&thread2, NULL, &philosopher_routine, NULL);
    pthread_create(&thread3, NULL, &philosopher_routine, NULL);

	
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
	printf("n = %d\n", n);
    return (0);
}