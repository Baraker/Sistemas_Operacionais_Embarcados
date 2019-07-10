1. Considere um MSP430 sendo usado para leituras analógicas. O Raspberry Pi está conectado a ele via UART. O MSP430 foi programado para converter e enviar dados de 10 bits a cada 10 ms. Escreva o código para o Raspberry Pi receber estes dados, e cada 1 segundo apresentar no terminal a média das últimas 100 amostras.

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define range 100
#define rangef (float)range

// Este codigo requer a biblioteca wringPi. Compile-o usando
//    gcc Ex4.c -lwiringPi -o Ex4.out

// Arquivo de acesso a porta serial
#define TTY "/dev/ttyAMA0"
// Arquivo de acesso a porta serial
// PARA O RASPBERRY PI 3
//#define TTY "/dev/ttyS0"

void* Display();
void* CODE();
void* vector_shift(unsigned char *arr);
void MA(unsigned char *moving_average, int data, int k);
void ctrl_c(int sig);


volatile float sum = 0;
int uart0_fd;

int main(){
	pthread_t t0, t1;

	pthread_create(&t0, NULL, CODE, NULL);
	pthread_create(&t1, NULL, Display, NULL);

	pthread_join(t0, NULL);
	pthread_join(t1, NULL);

	return 0;
}

void* Display(){
	usleep(1e06);
	while(1){
		usleep(1e06);
		printf("Média das últimas 100 amostras: %f\n", sum);
	}
	return NULL;
}

void* CODE(void)
{
	unsigned char msp430_input;
	int serial_status;

	signal(SIGINT, ctrl_c);
	uart0_fd = serialOpen(TTY, 9600);
	if(uart0_fd==-1)
	{
		puts("Erro abrindo a UART. Garanta que ela nao");
		puts("esteja sendo usada por outra aplicacao.");
		return -1;
	}
	if(wiringPiSetup() == -1)
	{
		puts("Erro em wiringPiSetup().");
		return -1;
	}
	puts(TTY " aberto.");
	puts("UART configurada:");
	system("stty -F " TTY);	//confere o resultado da configuração
	puts("");
	serialFlush(uart0_fd);

	unsigned char moving_average[range];
	int k = 0;

	while(1)
	{
		msp430_input = (unsigned char) serialGetchar(uart0_fd);
		serial_status = serialDataAvail(uart0_fd);
		if(serial_status==-1)
			printf("Erro = %s\n", strerror(errno));
		else
			printf("%d bytes disponiveis\n", serial_status);
		MA(moving_average, (int) msp430_input, k);
		if (k<range)
			k++;
		usleep(0.99 * 1e04);
	}
	serialClose(uart0_fd);
	return NULL;
}

void MA(unsigned char *moving_average, int data, int k){
	
	if(k == range){
		sum = sum - ((float)moving_average[0])/rangef;
		vector_shift(moving_average);
		moving_average[range-1] = data;
		sum = sum + ((float)moving_average[range-1])/rangef;
	}
	else
	{
		moving_average[k] = data;
		sum = sum + ((float)moving_average[k])/rangef;
	}
}

void* vector_shift(unsigned char *arr){
	for (int i = 0; i < range; i++) {
   		*(arr + i) = *(arr + i + 1);
	}
}

void ctrl_c(int sig)
{
	puts(" Fechando " TTY "...");
	serialClose(uart0_fd);
	exit(-1);
}
```

2. Considere um MSP430 sendo usado para leituras analógicas. O Raspberry Pi está conectado a ele via SPI, e é o mestre. O MSP430 foi programado para funcionar da seguinte forma:

- O MSP430 recebe o byte `0x55` e envia o byte `0xAA`, o que indica o começo de conversão. 
- 100us depois, o MSP430 recebe os bytes `0x01` e `0x02`, e envia o byte menos significativo e o mais significativo da conversão de 10 bits, nesta ordem.
 
Escreva o código para o Raspberry Pi executar este protocolo, de forma a obter conversões a cada 10 ms. A cada 1 segundo ele deve apresentar no terminal a média das últimas 100 amostras.

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <pthread.h>
#include <unistd.h>

#define range 100
#define rangef (float)range


// Este codigo requer a biblioteca wringPi. Compile-o usando
//    gcc Ex2.c -lwiringPi -o Ex2.out

void* Display();
void* CODE();
void* vector_shift(unsigned char *arr);
void MA(unsigned char *moving_average, int data, int k);
void ctrl_c(int sig);
int Start();

volatile float sum = 0;
int spi_fd;

int main(){
	pthread_t t0, t1;

	pthread_create(&t0, NULL, CODE, NULL);
	pthread_create(&t1, NULL, Display, NULL);

	pthread_join(t0, NULL);
	pthread_join(t1, NULL);

	return 0;
}

void *CODE(void){
	unsigned char send_msp430, nibbleLSB, nibbleMSB;
	int data, flag = 0;

	signal(SIGINT, ctrl_c);
	if(wiringPiSetup() == -1)
	{
		puts("Erro em wiringPiSetup().");
		return -1;
	}
	spi_fd = wiringPiSPISetup (0, 500000);
	if(spi_fd==-1)
	{
		puts("Erro abrindo a SPI. Garanta que ela nao");
		puts("esteja sendo usada por outra aplicacao.");
		return -1;
	}
	unsigned char moving_average[range];
	int k = 0;
	while(1)
	{
		while(flag != 1){
			flag = Start();
		}
		send_msp430 = 0x01;
		wiringPiSPIDataRW(0, &send_msp430, 1);
		usleep(0.5 * 1e4);
		nibbleLSB = send_msp430;
		send_msp430 = 0x02;
		wiringPiSPIDataRW(0, &send_msp430, 1);
		usleep(0.5 * 1e4);
		nibbleMSB = send_msp430;
		data = (nibbleMSB << 4) + nibbleLSB;
		MA(moving_average, data, k);
		if (k<range)
			k++;
		usleep(1e4);
	}
	close(spi_fd);
	return NULL;
}

void* Display(){
	usleep(1e6);
	while(1){
		usleep(1e06);
		printf("Média das últimas 100 amostras: %f\n", sum);
	}
	return NULL;
}

int Start(){
	unsigned char send_msp430;
	send_msp430 = 0x55;
	wiringPiSPIDataRW(0, &send_msp430, 1);
	if (send_msp430 == 0xAA){
		usleep(100);
		return 1;
	}
	else
		return 0;
}

void MA(unsigned char *moving_average, int data, int k){
	if(k == range){
		sum = sum - ((float)moving_average[0])/rangef;
		vector_shift(moving_average);
		moving_average[range-1] = data;
		sum = sum + ((float)moving_average[range-1])/rangef;
	}
	else
	{
		moving_average[k] = data;
		sum = sum + ((float)moving_average[k])/rangef;
	}
}

void* vector_shift(unsigned char *arr){
	for (int i = 0; i < range; i++) {
   		*(arr + i) = *(arr + i + 1);
	}
}

void ctrl_c(int sig){
	close(spi_fd);
	exit(-1);
}
```