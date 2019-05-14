1. Escreva um código em C para gerar uma onda quadrada de 1 Hz em um pino GPIO do Raspberry Pi.

```C
// Access from ARM Running Linux
#include <unistd.h>
#include "gpio_dev_mem.h"
"""
	Código para gerar uma onda quadrada de 1 Hz, ou um PWM de 1Hz com duty cycle de 500 ms;

	Pino de saída: pino 4;

"""

//Compile junto com o arquivo gpio_dev_mem.c
int main(int argc, char **argv)
{
	// Set up gpi pointer for direct register access
	setup_io();
	INP_GPIO(4);
	OUT_GPIO(4);

	while(1){
		GPIO_SET = 1<<4;
		usleep(500000000);
		GPIO_CLR = 1<<4;
	}

	return 0;
}
```

2. Generalize o código acima para qualquer frequência possível.

Versão 1
```C
// Access from ARM Running Linux
#include <unistd.h>
#include "gpio_dev_mem.h"

"""
	Código que gera onda quadrada dada uma frequência em Hz

	Frequência máxima = 10 kHz

"""

//Compile junto com o arquivo gpio_dev_mem.c
int main(int argc, char **argv)
{
	// Set up gpi pointer for direct register access
	setup_io();
	INP_GPIO(4);
	OUT_GPIO(4);

	float semi_period = 0, aux = 0;

	aux = atof(argv[1])

	if (aux > 10000) aux = 10000;

	semi_period = ((1 / aux) * 1000000000) / 2; // time in ns

	while(1){
		GPIO_SET = 1<<4;
		usleep(semi_period);
		GPIO_CLR = 1<<4;
	}

	return 0;
}
```
Versão 2
```C
#include <wiringPi.h>
#include <softPwm.h>

#define GPIO1 4

"""
	Código que gera onda quadrada dada uma frequência em Hz

	Frequência máxima = 10 kHz

"""

int main(int argc, char *argv[])
{

	float duty_cycle = 0, period = 0, aux = 0;

	aux = atof(argv[1])

	if (aux > 10000) aux = 10000;

	period = (1.0 / aux ) * 10000; // periodo * 100 us
	duty_cycle = period / 2; 

	if (wiringPiSetup() < 0) return 1;

	pinMode(GPIO1, OUTPUT);
	digitalWrite(GPIO1, LOW);
	softPwmCreate(GPIO1, 0, period);
	softPwmWrite(GPIO1, duty_cycle);

	while(1);

	return 0;
}
```

3. Crie dois processos, e faça com que o processo-filho gere uma onda quadrada, enquanto o processo-pai lê um botão no GPIO, aumentando a frequência da onda sempre que o botão for pressionado. A frequência da onda quadrada deve começar em 1 Hz, e dobrar cada vez que o botão for pressionado. A frequência máxima é de 64 Hz, devendo retornar a 1 Hz se o botão for pressionado novamente.

```C
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <wiringPi.h>
#include <softPwm.h>

#define GPIO1 4
#define button 29

"""

	Código cria onda quadrada (pwm com duty_cycle 50%) de 1 Hz e a cada vez que o usuário clicar no botão a frequência dobra até
	o limite de 64Hz e então volta para 1 Hz;

"""

void myInterrupt();

int flag = 0;

int main()
{

	int pid;
	int fd[2]; //fd filho to pai, fd1 pai to filho;

	float duty_cycle[7] = {5000, 2500, 1250, 625, 312.5, 156.25, 78.125}, period[7] = {10000, 5000, 2500, 1250, 625, 312.5, 156.25};
    // This initialises the wiringPi system 
    // and assumes that the calling program is going to be using the wiringPi pin numbering scheme.
    if(wiringPiSetup() < 0)return 1;

	// Cria o pipe
	pipe(fd);
	// Cria o processo
	pid = fork();


	// Codigo do filho
	if(pid == 0)
	{
		int i = 0;
		pinMode(GPIO1, OUTPUT);
		digitalWrite(GPIO1, LOW);
		softPwmCreate(GPIO1, 0, period[0]);
		softPwmWrite(GPIO1, duty_cycle[0]);

		char msg_pai[1];

		while(1)
		{

		if(read(fd[0], msg_pai, 1) < 0) 
			printf("Erro na leitura do pipe 1\n");
		else
			if(msg_pai == "1")
			{
				i = (i+1)%7;
				softPwmCreate(GPIO1, 0, period[i]);
				softPwmWrite(GPIO1, duty_cycle[i]);
				strcpy(msg_pai, "0");
			}

		}

	}


	// Codigo do Pai
	else
	{	
		// This function registers a function to received interrupts on the specified pin.
	    if(wiringPiISR(button, INT_EDGE_FALLING, &myInterrupt) < 0)
	    {  
	        printf("Unable to setup ISR \n");
	    }  

		char msg[1] = {"1"};

		while(1)
	    {
	        if(flag)
	        {  
	        	if(write(fd[0], msg, 1) < 0) 
					printf("Erro na escrita do pipe\n");

	            while(digitalRead(button) == 0);
	            printf("botão solto\n");
	            flag = 0;
	        }  
	    }  

	}

	return 0;
}

void myInterrupt()
{
	printf("botão pressionado\n");
    flag ++;
}
```









