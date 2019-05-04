/*

	Controle dos motores DC bidirecionais do Carrinho de controle remoto

	Esta função recebe instruções do controle remoto e escreve no GPIO para controlar a direção 

	para o controle dos motores serã o reservados os pinos:

	GPIO 16		L293D drive input 1A DC motor 1
	GPIO 19		L293D drive input 2A DC motor 1
	GPIO 20		L293D drive input 1A DC motor 2
	GPIO 21		L293D drive input 2A DC motor 2
	
	movimentos:
					GPIO16 		GPIO19 		GPIO20 		GPIO21
	
	W 				1			0 			0			1
	S 				0			1			1			0
	W+D
	W+A
	S+D
	S+A
	W+S
	W+D+A
	S+D+A
	W+D+A+S
*/

#include <stdio.h>
#include <stdlib.h>
#include "gpio_dev_mem.h"
#include <unistd.h>

#define active_time 1e+3

void movement(int gpio[4], int v_gpio[4]);

int main(){

	char c = 'W';

	// vetor que armazena o valor das portas GPIO16, GPIO19, GPIO20, GPIO21, respectivamente;
	int v_gpio[4];
	//vetor que armazena as portas
	int gpio[4] = {16, 19, 20, 21};
	
	setup_io();
	INP_GPIO(16);
	OUT_GPIO(16);
	
	INP_GPIO(19);
	OUT_GPIO(19);
	
	INP_GPIO(20);
	OUT_GPIO(20);

	INP_GPIO(21);
	OUT_GPIO(21);
	
	printf("maooooo");

	switch(c){
		// comando para andar para frente
		case('W'):
			v_gpio[0] = 1; v_gpio[1] = 0; v_gpio[2] = 0; v_gpio[3] = 1;
			movement(gpio, v_gpio);
			break;

//		case('A'):

//			break;
		// comando para andar para trás
		case('S'):
			v_gpio[0] = 0; v_gpio[1] = 1; v_gpio[2] = 1; v_gpio[3] = 0;
			movement(gpio, v_gpio);
			break;

//		case('D'):

//			break;
	}

	return 0;
}

void movement(int gpio[4], int v_gpio[4]){
 	for (int i = 0; i < 4; ++i)
 	{
		printf("maooo22");
		if(v_gpio[i]){
			//GPIO_SET = 1<<4;
			GPIO_SET = 1<<gpio[i];
			usleep(1e+3);
			//GPIO_CLR = 1<<gpio[i];
		}
 	}
}
