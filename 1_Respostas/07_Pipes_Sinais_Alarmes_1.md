1. Quantos pipes serão criados após as linhas de código a seguir? Por quê?

(a)
```C
int pid;
int fd[2];
pipe(fd);
pid = fork();
```
```txt
Serão criados 1 pipe, pois foi criado apenas 1 descritor de arquivos chamado 'fd[2]' e então ocorreu o fork, que por sua vez clonou os descritores de arquivos e entregou ao processo filho. Logo, neste caso, a pipe existente conecta o processo pai com o filho.  
```

(b)
```C
int pid;
int fd[2];
pid = fork();
pipe(fd);
```
```txt
Neste caso, o canal de comunicação, pipe, foi criado depois do fork e como os processos enxerguam os descritores de arquivo de forma não compartilhada duas pipes serão criadas e sem conexão uma com a outra.  
```

2. Apresente mais cinco sinais importantes do ambiente Unix, além do `SIGSEGV`, `SIGUSR1`, `SIGUSR2`, `SIGALRM` e `SIGINT`. Quais são suas características e utilidades?
```txt
  SIGCLD: é um sinal que trata da terminação de um processo filho e como default os processos filhos criam os chamados processos zumbis. Com o SIGCLD podemos ignorar a criação dos processos zumbis ou criar tratamentos para este evento.
  
  SIGPIPE: é um sinal que trata do evento de escrever em uma pipe não aberta em leitura.
  
  SIGKILL: é um sinal que não pode ser ignorado e mata o processo indicado.
  
  SIGSYS: é um sinal acionado quando ocorrem argumentos incorretos na chamada de um sistema.
  
  SIGQUIT: é um sinal emitido aos processos quando são acionadas as teclas de abandono: QUIT ou Ctrl + D.
```

3. Considere o código a seguir:

```C
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void tratamento_alarme(int sig)
{
	system("date");
	alarm(1);
}

int main()
{
	signal(SIGALRM, tratamento_alarme);
	alarm(1);
	printf("Aperte CTRL+C para acabar:\n");
	while(1);
	return 0;
}
```

Sabendo que a função `alarm()` tem como entrada a quantidade de segundos para terminar a contagem, quão precisos são os alarmes criados neste código? De onde vem a imprecisão? Este é um método confiável para desenvolver aplicações em tempo real?

Os alarmes possuem boa precisão, embora com o passar do tempo existe um erro acumulado que pode prejudicar aplicações em tempo real. A imprecisão vem pricipalmente do fato de que a CPU opera além do processo diversos outros então não possui dedicação total para reduzir o erro acumulado e também a chamada das funções corroboram com essa essa discrepância temporal.