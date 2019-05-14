1. Crie dois processos, e faça com que o processo-filho gere uma onda quadrada, enquanto o processo-pai faz polling de um botão no GPIO, aumentando a frequência da onda sempre que o botão for pressionado. A frequência da onda quadrada deve começar em 1 Hz, e dobrar cada vez que o botão for pressionado. A frequência máxima é de 64 Hz, devendo retornar a 1 Hz se o botão for pressionado novamente.

```C
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <sys/poll.h>
#include <fcntl.h>

#define GPIO1 4
#define N 1000
#define Nlim (N*3)/4

"""

	Código cria onda quadrada (pwm com duty_cycle 50%) de 1 Hz e a cada vez que o usuário clicar no botão a frequência dobra até
	o limite de 64Hz e então volta para 1 Hz;

"""

void poll_btn(struct pollfd *pfd);

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
	    struct pollfd pfd;
		int btn_press;
		system("echo 4     > /sys/class/gpio/export");
		system("echo falling  > /sys/class/gpio/gpio4/edge");
		system("echo in    > /sys/class/gpio/gpio4/direction");
		pfd.fd = open("/sys/class/gpio/gpio4/value", O_RDONLY);
		if(pfd.fd < 0)
		{
			puts("Erro abrindo /sys/class/gpio/gpio4/value");
			puts("Execute este programa como root.");
			return 1;
		}
		pfd.events = POLLPRI | POLLERR;
		pfd.revents = 0;

		char msg[1] = {"1"};

		while(1)
	    {
	    	poll_btn(&pfd);
			puts("Botão pressionado!");
	        if(flag)
	        {  
	        	if(write(fd[0], msg, 1) < 0) 
					printf("Erro na escrita do pipe\n");

	            while(digitalRead(button) == 0);
	            printf("botão solto\n");
	            flag = 0;
	        }  
	    }
	    close(pfd.fd);
		system("echo 4 > /sys/class/gpio/unexport");  

	}

	return 0;
}

void poll_btn(struct pollfd *pfd)
{
	char buffer, vals[N] = {0};
	int pos = 0, test=1, i, s;
	lseek(pfd->fd, 0, SEEK_SET);
	read(pfd->fd, &buffer, 1);
	for(i=0;i<N;i++) vals[i] = buffer-'0';
	poll(pfd, 1, -1);
	while(test)
	{
		lseek(pfd->fd, 0, SEEK_SET);
		read(pfd->fd, vals+pos, 1);
		vals[pos] -= '0';
		pos = (pos+1)%N;
		for(s=i=0; i<N; i++)
			s += vals[i];
		if(buffer=='0')
			test = s<Nlim;
		else
			test = s>Nlim;
	}
	flag++;
}
```