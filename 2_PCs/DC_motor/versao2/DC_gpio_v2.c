
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
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define NUMBER_GPIO 4
#define GPIO16 "16"
#define GPIO19 "19"
#define GPIO20 "20"
#define GPIO21 "21"
#define active_time 1e+6

void movement(char gpio[4][2], char v_gpio[4]);

int main(){

	char c;

	scanf("%c", &c);

	// vetor que armazena o valor das portas GPIO16, GPIO19, GPIO20, GPIO21, respectivamente;
	char v_gpio[4];
	//vetor que armazena as portas
	char gpio[4][2] = {GPIO16, GPIO19, GPIO20, GPIO21};

	switch(c){
		// comando para andar para frente
		case('W'):
			v_gpio[0] = '1'; v_gpio[1] = '0'; v_gpio[2] = '0'; v_gpio[3] = '1';
			movement(gpio, v_gpio);
			printf("controle: %c\n", c);
			break;

//		case('A'):

//			break;
		// comando para andar para trás
		case('S'):
			v_gpio[0] = '0'; v_gpio[1] = '1'; v_gpio[2] = '1'; v_gpio[3] = '0';
			movement(gpio, v_gpio);
			break;

//		case('D'):

//			break;
	}

	main();

	return 0;
}

void movement(char gpio[4][2], char v_gpio[4]){
	char string[40] = {"echo 1 > /sys/class/gpio/gpioxx/value"};
 	
 	string[5] = '1';
	for (int i = 0; i < NUMBER_GPIO; ++i)
 	{
 		if(v_gpio[i] == '1'){
 			string[29] = gpio[i][0];string[30] = gpio[i][1];
 			system(string);
 			printf("%s\n", string);
 		}
 	}

 	usleep(active_time);
 	
 	string[5] = '0';
	for (int i = 0; i < NUMBER_GPIO; ++i)
	{
		if(v_gpio[i] == '1'){
 			string[29] = gpio[i][0];string[30] = gpio[i][1];
 			system(string);
 			printf("%s\n", string);
		}
	}
 }
