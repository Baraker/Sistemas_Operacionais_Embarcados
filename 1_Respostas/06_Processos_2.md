1. Crie um código em C para gerar três processos-filho usando o `fork()`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NUMBER_FORK 3

void func_fork(int i);

int main(int argc, const char *argv[])
{
	
	func_fork(0);
	
	return 0;
}

 void func_fork(int i){
 	pid_t pid_aux = fork();
 	if (pid_aux == 0)	// se for o processo filho, deve executar um novo processo e matar este processo filho;
 	{	
 		printf("* O ID de processo filho eh %d.\n", (int) getpid ());

 	}
 	else				// se for o processo pai, deve forkar para gerar novos processos descartáveis até executar todos os comandos
 	{
 		printf("* O ID de processo pai eh %d.\n", (int) getpid ());
 		if (NUMBER_FORK != (i+1))
 		{
 			sleep(1);
 			printf("\n");
			func_fork1(i+1);
		}
 	}

 }
```

2. Crie um código em C que recebe o nome de diversos comandos pelos argumentos de entrada (`argc` e `*argv[]`), e executa cada um sequencialmente usando `system()`. Por exemplo, considerando que o código criado recebeu o nome de 'serial_system', e que ele foi executado na pasta '/Sistemas_Embarcados/Code/06_Processos', que contem diversos arquivos:

```bash
$ ./serial_system pwd echo ls echo cal
$ ~/Sistemas_Embarcados/Code/06_Processos
$
$ Ex1.c    Ex2b.c   Ex4.c   Ex6.c
$ Ex2a.c   Ex3.c    Ex5.c   serial_system
$
$     Março 2017
$ Do Se Te Qu Qu Se Sá
$           1  2  3  4
$  5  6  7  8  9 10 11
$ 12 13 14 15 16 17 18
$ 19 20 21 22 23 24 25
$ 26 27 28 29 30 31
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void serial_system(int argc, const char *argv[], int i);

int main(int argc, const char *argv[])
{
	if (argc < 2)
	{
		printf("Insira Argumentos de Entrada!\n" );
		return 0;
	}
	else
		serial_system( argc, argv, 0);
	
	return 0;
}

void serial_system( int argc, const char *argv[], int i){

	system(argv[i+1]);
	if (argc != (i+2))
	{
		printf("\n");
		serial_system(argc, argv, i+1);
	}
 }
```

3. Crie um código em C que recebe o nome de diversos comandos pelos argumentos de entrada (`argc` e `*argv[]`), e executa cada um usando `fork()` e `exec()`.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void func_fork(int argc, const char *argv[], int i);

int main(int argc, const char *argv[])
{
	if (argc < 2)
	{
		printf("Insira Argumentos de Entrada!\n" );
		return 0;
	}
	else
		func_fork( argc, argv, 0);
	
	return 0;
}

 void func_fork( int argc, const char *argv[], int i){
 	pid_t pid_aux = fork();
 	if (pid_aux == 0)	// se for o processo filho, deve executar um novo processo e matar este processo filho;
 	{	
 		printf("* O ID de processo filho eh %d.\n", (int) getpid ());
 		char * lista_de_argumentos[] = {argv[i+1], NULL};
 		execvp(lista_de_argumentos[0], lista_de_argumentos);

 	}
 	else				// se for o processo pai, deve forkar para gerar novos processos descartáveis até executar todos os comandos
 	{
 		printf("* O ID de processo pai eh %d.\n", (int) getpid ());
 		if (argc != (i+2))
 		{
 			sleep(1);
 			printf("\n");
			func_fork(argc, argv, i+1);
		}
 	}
 }
```

4. Crie um código em C que gera três processos-filho usando o `fork()`, e que cada processo-filho chama a seguinte função uma vez:

```C
int v_global = 0; // Variavel global para este exemplo
void Incrementa_Variavel_Global(pid_t id_atual)
{
	v_global++;
	printf("ID do processo que executou esta funcao = %d\n", id_atual);
	printf("v_global = %d\n", v_global);
}
```

(Repare que a função `Incrementa_Variavel_Global()` recebe como entrada o ID do processo que a chamou.) Responda: a variável global `v_global` foi compartilhada por todos os processos-filho, ou cada processo enxergou um valor diferente para esta variável?  
  
A variável não foi compartilhada pelos processos. Como todos os forks vieram do processo pai, então os processos filhos exergaram a cópia da variável que consta no processo pai.  
  
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NUMBER_FORK 3

void func_fork(int i);
void Incrementa_Variavel_Global(pid_t id_atual);

int v_global = 0;

int main(int argc, const char *argv[])
{
	
	func_fork(0);
	
	return 0;
}

 void func_fork(int i){
 	pid_t pid_aux = fork();
 	if (pid_aux == 0)	// se for o processo filho, deve executar um novo processo e matar este processo filho;
 	{	
 		Incrementa_Variavel_Global((int) getpid());
 	}
 	else				// se for o processo pai, deve forkar para gerar novos processos descartáveis até executar todos os comandos
 	{
 		if (NUMBER_FORK != (i+1))
 		{
 			sleep(1);
 			printf("\n");
			func_fork(i+1);
		}
 	}
 }

void Incrementa_Variavel_Global(pid_t id_atual)
{
	v_global++;
	printf("ID do processo que executou esta funcao = %d\n", id_atual);
	printf("v_global = %d\n", v_global);
}
```

5. Repita a questão anterior, mas desta vez faça com que o processo-pai também chame a função `Incrementa_Variavel_Global()`. Responda: a variável global `v_global` foi compartilhada por todos os processos-filho e o processo-pai, ou cada processo enxergou um valor diferente para esta variável?  
  
Novamente os processos filhos não compartilharam o valor da variável mesmo que os prints mostrem a variável crescendo juntO. A questão é que como também foi executado a função de incrementação da variável através do processo pai, os processos filhos visualizaram valores diferentes a medida que o programa os criou pela função fork().

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NUMBER_FORK 3

void func_fork(int i);
void Incrementa_Variavel_Global(pid_t id_atual);

int v_global = 0;

int main(int argc, const char *argv[])
{
	
	func_fork(0);
	
	return 0;
}

 void func_fork(int i){
 	pid_t pid_aux = fork();
 	if (pid_aux == 0)	// se for o processo filho, deve executar um novo processo e matar este processo filho;
 	{	
 		Incrementa_Variavel_Global((int) getpid());
 	}
 	else				// se for o processo pai, deve forkar para gerar novos processos descartáveis até executar todos os comandos
 	{
 		Incrementa_Variavel_Global((int) getpid());
 		if (NUMBER_FORK != (i+1))
 		{
 			sleep(1);
 			printf("\n");
			func_fork(i+1);
		}
 	}
 }

void Incrementa_Variavel_Global(pid_t id_atual)
{
	v_global++;
	printf("ID do processo que executou esta funcao = %d\n", id_atual);
	printf("v_global = %d\n", v_global);
}
```