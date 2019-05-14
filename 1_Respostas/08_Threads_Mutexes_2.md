1. Crie um programa em C que cria uma thread, e faça com que o programa principal envie os valores 1, 2, 3, 4, 5, 6, 7, 8, 9 e 10 para a thread, com intervalos de 1 segundo entre cada envio. Depois de o programa principal enviar o número 10, ele aguarda 1 segundo e termina a execução. A thread escreve na tela cada valor recebido, e quando ela receber o valor 10, ela termina a execução.

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

volatile int buffer = 0;

sem_t sem;

// Função que incrementa o Contador
void* controle (void *arg)
{
	int vector;

	while (1)
	{			
		vector = buffer;
		printf("%d\n", vector);
		sem_post(&sem);
		if (vector == 10)
			return NULL;
		else
			sleep(1);
	}
	return NULL;

}


int main (int argc, char** argv)
{
	pthread_t t0;
	sem_init(&sem, 0, 0);
	printf("Valor inicial: %d\n", buffer);	
	pthread_create(&t0, NULL, controle, NULL);

	for (unsigned int i=1; i <= 10; i++)
	{
		buffer = i;
		sem_wait(&sem);
	}

	sleep(1);

	sem_destroy(&sem);

	printf("Valor final: %d\n", buffer);
	return 0;
}
```

2. Crie um programa em C que preenche o vetor `long int v[50000]` completamente com valores aleatórios (use a função `random()`), e que procura o valor máximo do vetor por dois métodos:

(a) Pela busca completa no vetor `v[]`;

```C
// Exemplo do Concorrência em Threads

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char** argv)
{
	clock_t begin = clock();
	long int v[50000];
	long int max_value = 0;
	srand(time(0));

	for (int i = 0; i < 50000; ++i)
	{
		v[i] = rand();
	}

	for (int i = 0; i < 50000; ++i)
	{
		if (v[i] > max_value)
			max_value = v[i];
	}

	printf("Valor máximo encontrado: %ld\n", max_value);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Tempo de execução: %lf\n", time_spent );
	return 0;
}
```

(b) Separando o vetor em 4 partes, e usando 4 threads para cada uma encontrar o máximo de cada parte. Ao final das threads, o programa principal compara o resultado das quatro threads para definir o máximo do vetor.

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

volatile long int max_value_vector[4] = {0, 0, 0, 0};
volatile int ordenador = 0; 

static pthread_mutex_t mutexLock;

void* thread_mv (void *li_vector)
{
	int flag = 1, j;
	long int *long_int_v = (long int *) li_vector;
	for (unsigned int i=0; i < 12500; i++)
	{
		pthread_mutex_lock(&mutexLock);
		if (flag)
		{
			j = ordenador;
			ordenador++;
			flag = 0;
		}
		if ( *(long_int_v + i) > max_value_vector[j] )
			max_value_vector[j] = *(long_int_v + i);
		pthread_mutex_unlock(&mutexLock);
	}
	return NULL;
}


int main (int argc, char** argv)
{
	clock_t begin = clock();
	
	pthread_t t0, t1, t2, t3;

	pthread_mutex_init(&mutexLock, NULL);

	long int *v = (long int*)malloc(50000*sizeof(long int));
	long int max_value = 0;

	srand(time(0));

	for (int i = 0; i < 50000; ++i)
	{
		v[i] = (long int) rand();
	}

	pthread_create(&t0, NULL, thread_mv, &v[0]);
	pthread_create(&t1, NULL, thread_mv, &v[12500-1]);
	pthread_create(&t2, NULL, thread_mv, &v[25000-1]);
	pthread_create(&t3, NULL, thread_mv, &v[37500-1]);
	
	pthread_join(t0, NULL);
	pthread_join(t1, NULL);	
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	pthread_mutex_destroy(&mutexLock);

	free(v);

	for (int j = 0; j < 4; ++j)
	{
		if(max_value_vector[j] > max_value)
			max_value = max_value_vector[j];
	}

	printf("Valor máximo encontrado: %ld\n", max_value);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Tempo de execução: %lf\n", time_spent );

	return 0;
}
```

Ao final do programa principal, compare os resultados obtidos pelos dois métodos.

3. Repita o exercício anterior, mas calcule a média do vetor ao invés do valor máximo.

Parte (a)
```C
// Exemplo do Concorrência em Threads

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char** argv)
{
	clock_t begin = clock();
	long int v[50000];
	long int sum = 0;
	srand(time(0));

	for (int i = 0; i < 50000; ++i)
	{
		v[i] = rand();
	}

	for (int i = 0; i < 50000; ++i)
	{
		sum += v[i] / 50000;
	}

	printf("Média encontrada: %ld\n", sum);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Tempo de execução: %lf\n", time_spent );
	return 0;
}
```

Parte (b)
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

volatile long int average_vector[4] = {0, 0, 0, 0};
volatile int ordenador = 0; 

static pthread_mutex_t mutexLock;

void* thread_mv (void *li_vector)
{
	int flag = 1, j;
	long int *long_int_v = (long int *) li_vector;
	for (unsigned int i=0; i < 12500; i++)
	{
		pthread_mutex_lock(&mutexLock);
		if (flag)
		{
			j = ordenador;
			ordenador++;
			flag = 0;
		}
		average_vector[j] += *(long_int_v + i) / 50000;
		pthread_mutex_unlock(&mutexLock);
	}
	return NULL;
}


int main (int argc, char** argv)
{
	clock_t begin = clock();
	
	pthread_t t0, t1, t2, t3;

	pthread_mutex_init(&mutexLock, NULL);

	long int *v = (long int*)malloc(50000*sizeof(long int));
	long int average = 0;

	srand(time(0));

	for (int i = 0; i < 50000; ++i)
	{
		v[i] = (long int) rand();
	}

	pthread_create(&t0, NULL, thread_mv, &v[0]);
	pthread_create(&t1, NULL, thread_mv, &v[12500-1]);
	pthread_create(&t2, NULL, thread_mv, &v[25000-1]);
	pthread_create(&t3, NULL, thread_mv, &v[37500-1]);
	
	pthread_join(t0, NULL);
	pthread_join(t1, NULL);	
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	pthread_mutex_destroy(&mutexLock);

	free(v);

	for (int j = 0; j < 4; ++j)
	{
			average += average_vector[j];
	}

	printf("Média encontrado: %ld\n", average);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Tempo de execução: %lf\n", time_spent );

	return 0;
}
```

4. Repita o exercício anterior, mas calcule a variância do vetor ao invés da média.

Parte (a)
```C
// Exemplo do Concorrência em Threads

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char** argv)
{
	clock_t begin = clock();
	long int v[50000];
	long int average = 0, average2 = 0, var = 0;
	srand(time(0));

	for (int i = 0; i < 50000; ++i)
	{
		v[i] = rand();
	}

	for (int i = 0; i < 50000; ++i)
	{
		average += v[i] / 50000;
		average2 += v[i]*v[i] / 50000;
	}

	var = average2 - average*average;

	printf("Média encontrada: %ld\n", average);
	printf("Variância encontrada: %ld\n", var);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Tempo de execução: %lf\n", time_spent );
	return 0;
}
```

Parte (b)
```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

volatile long int average_vector[4] = {0, 0, 0, 0};
volatile long int average2_vector[4] = {0, 0, 0, 0};
volatile int ordenador = 0; 

static pthread_mutex_t mutexLock;

void* thread_mv (void *li_vector)
{
	int flag = 1, j;
	long int *long_int_v = (long int *) li_vector;
	for (unsigned int i=0; i < 12500; i++)
	{
		pthread_mutex_lock(&mutexLock);
		if (flag)
		{
			j = ordenador;
			ordenador++;
			flag = 0;
		}
		average_vector[j] += *(long_int_v + i) / 50000;
		average2_vector[j] += ( *(long_int_v + i) * *(long_int_v + i) ) / 50000;
		pthread_mutex_unlock(&mutexLock);
	}
	return NULL;
}


int main (int argc, char** argv)
{
	clock_t begin = clock();
	
	pthread_t t0, t1, t2, t3;

	pthread_mutex_init(&mutexLock, NULL);

	long int *v = (long int*)malloc(50000*sizeof(long int));
	long int average = 0, average2 = 0, var = 0;

	srand(time(0));

	for (int i = 0; i < 50000; ++i)
	{
		v[i] = (long int) rand();
	}

	pthread_create(&t0, NULL, thread_mv, &v[0]);
	pthread_create(&t1, NULL, thread_mv, &v[12500-1]);
	pthread_create(&t2, NULL, thread_mv, &v[25000-1]);
	pthread_create(&t3, NULL, thread_mv, &v[37500-1]);
	
	pthread_join(t0, NULL);
	pthread_join(t1, NULL);	
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	pthread_mutex_destroy(&mutexLock);

	free(v);

	for (int j = 0; j < 4; ++j)
	{
			average += average_vector[j];
			average2 += average2_vector[j];
	}

	var = average2 - average*average;

	printf("Média encontrada: %ld\n", average);
	printf("Variância encontrada: %ld\n", var);

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Tempo de execução: %lf\n", time_spent );

	return 0;
}
```