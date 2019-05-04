/*
	Pinos de PWM

	PWM0: 12; PWM1: 13

	cordenadas de entrada: phi, teta

	phi 	= ângulo entre o vetor e o eixo Z
	teta 	= ângulo entre o vetor e oixo X

	phi 	= acos( z / raiz(x² + y² + z²) )
	teta	= atang( y / x )

	saída: duty_cycle em nano segundos dos PWMs baseado em teta e phi
	
	período do PWM em nano segundos = 20000000

	ângulo (graus)		duty_cycle (ns) 	duty_cycle (ms)
	0					1000000	ou 500000	1 ou 0.5
	90					1500000				
	180					2000000 ou 2500000	2 ou 2.5

	considerando 	duty_cycle(0°) 		= 1000000
					duty_cycle(180°) 	= 2000000
	
	faixa de operação 1000000 ns

	duty_cycle(x°) = 1000000 + x° * 5555.555

	considerando a outra faixa de operação de 2000000 ns

	duty_cycle(x°) = 500000 + x° * 11111.111
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846

int main(int argc, const char * argv[]) {

	//ponteiro para string dos caminhos para escrita nos arquivos de [0] pwm0, [1] pwm1
	char *pwm_file_path[2];
	char aux[100];
	// variável para armazenar os duty_cycles de [0] pwm0, [1] pwm1
	float DC_pwm[2];
	// variável para armazenar os ângulos de [0] phi, [1] teta
	float angle[2];
	// variáveis para armazenar phi e teta;
	float phi = 0, teta = 0;

	if (argc < 2)
	{
		printf("Insira Argumentos de Entrada!\n" );
		return 0;
	}

	phi = atof(argv[1]);
	teta = atof(argv[2]);


	// cálculo de phi:
 	angle[0] = phi;

 	// cálculo de teta:
 	angle[1] = teta + 90.0;

	DC_pwm[0] = 550000 + angle[0] * 9166.6;

	DC_pwm[1] = 550000 + angle[1] * 9166.6;

	printf("%f\n%f\n", DC_pwm[0], DC_pwm[1]);

	pwm_file_path[0] = (char*)malloc(39*sizeof(char));
	pwm_file_path[1] = (char*)malloc(39*sizeof(char));

	strcpy(pwm_file_path[0],  "/sys/class/pwm/pwmchip0/pwm0/duty_cycle");
	strcpy(pwm_file_path[1],  "/sys/class/pwm/pwmchip0/pwm1/duty_cycle");

	//system("echo 2500000 > /sys/class/pwm/pwmchip0/pwm0/duty_cycle");

	for (int i = 0; i < 2; ++i)
	{
		sprintf(aux, "echo %.0f > %s", DC_pwm[i], pwm_file_path[i]);
		printf("%s\n",aux);
		system(aux);

	}

	free(pwm_file_path[0]);
	free(pwm_file_path[1]);

	return 0;
}
