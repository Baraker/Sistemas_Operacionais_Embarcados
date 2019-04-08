1. Crie um programa em C que cria um processo-filho e um pipe de comunicação. Faça com que o processo-pai envie os valores 1, 2, 3, 4, 5, 6, 7, 8, 9 e 10 para o processo-filho, com intervalos de 1 segundo entre cada envio. Depois de o processo-pai enviar o número 10, ele aguarda 1 segundo e termina a execução. O processo-filho escreve na tela cada valor recebido, e quando ele receber o valor 10, ele termina a execução.
  
```C
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define count 10

int main()
{
	int pid;
	int fd[2];
	// Cria o pipe
	pipe(fd);
	// Cria o processo
	pid = fork();
	// Codigo do filho
	if(pid == 0)
	{
		char buffer_filho[1];
		for (int i = 0; i < count; ++i)
		{
			if(read(fd[0], buffer_filho, 1) < 0) 
				printf("Erro na leitura do pipe\n");
			else{
				printf("Valor lido pelo filho = %d\n", (int) buffer_filho[0]);
				if ((int) buffer_filho[0] == count)
					exit(1);					
			}
		}
	}
	// Codigo do pai
	else
	{
		char aux;
		char msg_pai[1];
		for (int i = 1; i <= count; ++i)
		{
			aux = (char) i;
			strcpy(msg_pai, &aux);
			if (write(fd[1], msg_pai, 1) < 0)
				printf("Erro na escrita do pipe\n");
			else
				printf("Valor enviado pelo Pai = %d\n", (int)msg_pai[0]);
			sleep(1);
			if(i == count)
				exit(1);

		}
	}
	return 0;
}

```

2. Crie um programa em C que cria um processo-filho e um pipe de comunicação. Utilize o pipe para executar a seguinte conversa entre processos:

```
FILHO: Pai, qual é a verdadeira essência da sabedoria?
PAI: Não façais nada violento, praticai somente aquilo que é justo e equilibrado.
FILHO: Mas até uma criança de três anos sabe disso!
PAI: Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...
```
Neste exercício, quem recebe a mensagem via pipe é quem as escreve no terminal.

```C
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int pid;
	int fd[2];
	// Cria o pipe
	pipe(fd);
	// Cria o processo
	pid = fork();
	// Codigo do filho
	if(pid == 0)
	{
		char buffer_filho[100]; 
		char *msg_filho[2];
		msg_filho[0] = (char*)malloc(49 * sizeof(char));
		msg_filho[1] = (char*)malloc(46 * sizeof(char));
		strcpy(msg_filho[0], "Pai, qual é a verdadeira essência da sabedoria?");
		strcpy(msg_filho[1], "Mas até uma criança de três anos sabe disso!");

		//printf("%s\n%ld\n", msg_filho[0], strlen(msg_filho[0]));
		//primeira mensagem eviada
		if (write(fd[1], msg_filho[0], 100) < 0)
			printf("Erro na escrita do pipe\n");
		usleep(1000000);

		//segunda mensagem recebida
		if(read(fd[0], buffer_filho, 100) < 0) 
			printf("Erro na leitura do pipe\n");
		else
			printf("Pai: %s\n", buffer_filho);

		//terceira mensagem eviada
		if (write(fd[1], msg_filho[1], 100) < 0)
			printf("Erro na escrita do pipe\n");
		usleep(1000000);

		//quarta mensagem recebida
		if(read(fd[0], buffer_filho, 100) < 0) 
			printf("Erro na leitura do pipe\n");
		else
			printf("Pai: %s\n", buffer_filho);
		
		free(msg_filho[0]);
		free(msg_filho[1]);	
	}

	// Codigo do pai
	else
	{
		char buffer_pai[100];
		char *msg_pai[2];
		msg_pai[0] = (char*)malloc(78 * sizeof(char));
		msg_pai[1] = (char*)malloc(81 * sizeof(char));
		strcpy(msg_pai[0], "Não façais nada violento, praticai somente aquilo que é justo e equilibrado.");
		strcpy(msg_pai[1], "Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...");
		
		//primeira mensagem recebida
		if(read(fd[0], buffer_pai, 100) < 0) 
			printf("Erro na leitura do pipe\n");
		else
			printf("Filho: %s\n", buffer_pai);

		//segunda mensagem enviada
		if (write(fd[1], msg_pai[0], 100) < 0)
			printf("Erro na escrita do pipe\n");
		usleep(1000000);

		//terceira mensagem recebida
		if(read(fd[0], buffer_pai, 100) < 0) 
			printf("Erro na leitura do pipe\n");
		else
			printf("Filho: %s\n", buffer_pai);

		//quarta mensagem enviada
		if (write(fd[1], msg_pai[1], 100) < 0)
			printf("Erro na escrita do pipe\n");
		usleep(1000000);

		free(msg_pai[0]);
		free(msg_pai[1]);

	}
	return 0;
}
```

3. Crie um programa em C que cria dois processos-filhos e um pipe de comunicação. Utilize o pipe para executar a seguinte conversa entre processos:

```
FILHO1: Quando o vento passa, é a bandeira que se move.
FILHO2: Não, é o vento que se move.
PAI: Os dois se enganam. É a mente dos senhores que se move.
```

Neste exercício, quem recebe a mensagem via pipe é quem as escreve no terminal.

```C
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int pid;
	int fd[2];
	// Cria o pipe
	pipe(fd);
	// Cria o processo
	pid = fork();

	// Codigo do filho 1
	if(pid == 0)
	{
		char buffer_filho1[100];
		char *msg_filho1;
		msg_filho1 = (char*)malloc(49 * sizeof(char));
		strcpy(msg_filho1, "Quando o vento passa, é a bandeira que se move.");

		//primeira mensagem eviada
		if (write(fd[1], msg_filho1, 100) < 0)
			printf("Erro na escrita do pipe\n");
		usleep(2000000);

		// terceira mensagem recebida
		if(read(fd[0], buffer_filho1, 100) < 0) 
			printf("Erro na leitura do pipe\n");
		else
			printf("Pai: %s\n", buffer_filho1);

		free(msg_filho1);
	}

	// Codigo do Pai
	else
	{
		int pid2;
		pid2 = fork();

		// Código do filho 2
		if (pid2 == 0)
		{
			char buffer_filho2[100];
			char *msg_filho2;
			msg_filho2 = (char*)malloc(29 * sizeof(char));
			strcpy(msg_filho2, "Não, é o vento que se move.");

			//primeira mensagem recebida
			if(read(fd[0], buffer_filho2, 100) < 0) 
				printf("Erro na leitura do pipe\n");
			else
				printf("Filho1: %s\n", buffer_filho2);

			//segunda mensagem enviada
			if (write(fd[1], msg_filho2, 100) < 0)
				printf("Erro na escrita do pipe\n");

			free(msg_filho2);
		}

		// Código do Pai
		else{

			char buffer_pai[100];
			char *msg_pai;
			msg_pai = (char*)malloc(57 * sizeof(char));
			strcpy(msg_pai, "Os dois se enganam. É a mente dos senhores que se move.");

			usleep(1000000);

			//segunda mensagem recebida
			if(read(fd[0], buffer_pai, 100) < 0) 
				printf("Erro na leitura do pipe\n");
			else
				printf("Filho2: %s\n", buffer_pai);

			//terceira mensagem enviada
			if (write(fd[1], msg_pai, 100) < 0)
				printf("Erro na escrita do pipe\n");

			usleep(1000000);

			free(msg_pai);

		}
	}

	return 0;
}
```

4. Crie um programa em C que cria um processo-filho e um pipe de comunicação. O processo-filho deverá pedir o nome do usuário, envia-lo para o pai via pipe, e o pai deverá escrever o nome do usuário no terminal.

```C
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void DMscan(char * string);

int main()
{
	int pid;
	int fd[2];
	// Cria o pipe
	pipe(fd);
	// Cria o processo
	pid = fork();

	// Codigo do filho
	if(pid == 0)
	{
		char *msg_filho;
		msg_filho = (char*)malloc(sizeof(char));
		
		printf("Filho - Digite o seu nome: ");
		DMscan(msg_filho);

		//primeira mensagem eviada
		if (write(fd[1], msg_filho, 100) < 0)
			printf("Erro na escrita do pipe\n");

		free(msg_filho);
	}

	// Codigo do Pai
	else
	{
		char buffer_pai[100];

		//primeira mensagem recebida
		if(read(fd[0], buffer_pai, 100) < 0) 
			printf("Erro na leitura do pipe\n");
		else
			printf("Pai - Seu nome é: %s\n", buffer_pai);

	}

	return 0;
}

void DMscan(char * string){
	char aux = 0;
	int i = 0;
	while(scanf("%c", &aux) == 1 && aux != '\n'){
		string[i] = aux;
		i++;
		string = (char*)realloc(string, (i+1) * sizeof(char));
	}
}
```

5. Utilize o sinal de alarme para chamar a cada segundo o comando `ps` ordenando todos os processos de acordo com o uso da CPU. Ou seja, seu código atualizará a lista de processos a cada segundo. Além disso, o código deverá tratar o sinal do CTRL-C, escrevendo "Processo terminado!" na tela antes de terminar a execução do processo.

```C
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void tratamento_alarme(int sig)
{
	alarm(1);
	system("ps");
	printf("\n");
}

void funcao_para_control_c()
{
	printf("\nProcesso terminado!\n");
	exit(1);
}

int main()
{	
	signal(SIGINT, funcao_para_control_c);
	signal(SIGALRM, tratamento_alarme);
	alarm(1);
	printf("Aperte CTRL+C para acabar:\n");
	while(1);
	return 0;
}

```