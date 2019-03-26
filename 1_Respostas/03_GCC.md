Para todas as questões, compile-as com o gcc e execute-as via terminal.

1. Crie um "Olá mundo!" em C.

```código 
#include <stdio.h>

int main(){
        printf("Olá mundo!\n");
return 0;
}
```

2. Crie um código em C que pergunta ao usuário o seu nome, e imprime no terminal "Ola " e o nome do usuário. Por exemplo, considerando que o código criado recebeu o nome de 'ola_usuario_1':

```bash
$ ./ola_usuario_1
$ Digite o seu nome: Eu
$ Ola Eu
```
```código
#include <stdio.h>
#include <stdlib.h>

int main(){

int i=0;
char *c;
char aux;

c = (char*)malloc(sizeof(char));
printf("Digite o seu nome: ");

while(scanf("%c", &aux) == 1 && aux != '\n'){
        c[i] = aux;
        i++;
        c = (char*)realloc(c, (i+1) * sizeof(char));
}

printf("Ola %s\n", c);
return 0;

}

```


3. Apresente os comportamentos do código anterior nos seguintes casos:

(a) Se o usuário insere mais de um nome.
```bash
$ ./ola_usuario_1
$ Digite o seu nome: Eu Mesmo
```
Ola Eu mesmo  

(b) Se o usuário insere mais de um nome entre aspas duplas. Por exemplo:
```bash
$ ./ola_usuario_1
$ Digite o seu nome: "Eu Mesmo"
```
Ola "Eu mesmo"  

(c) Se é usado um pipe. Por exemplo:
```bash
$ echo Eu | ./ola_usuario_1
```
Digite o seu nome: Ola Eu  

(d) Se é usado um pipe com mais de um nome. Por exemplo:
```bash
$ echo Eu Mesmo | ./ola_usuario_1
```
Digite o seu nome: Ola Eu Mesmo  

(e) Se é usado um pipe com mais de um nome entre aspas duplas. Por exemplo:
```bash
$ echo "Eu Mesmo" | ./ola_usuario_1
```
Digite o seu nome: Ola Eu Mesmo  

(f) Se é usado o redirecionamento de arquivo. Por exemplo:
```bash
$ echo Ola mundo cruel! > ola.txt
$ ./ola_usuario_1 < ola.txt
```
Digite o seu nome: Ola Ola mundo cruel!  

4. Crie um código em C que recebe o nome do usuário como um argumento de entrada (usando as variáveis argc e *argv[]), e imprime no terminal "Ola " e o nome do usuário. Por exemplo, considerando que o código criado recebeu o nome de 'ola_usuario_2':

```bash
$ ./ola_usuario_2 Eu
$ Ola Eu
```
```código
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	printf("Ola ");
	for (int i = 1; i < argc; ++i)
	{
		printf("%s ", argv[i]);
	}
	printf("\n");
	return 0;

}

```

5. Apresente os comportamentos do código anterior nos seguintes casos:

(a) Se o usuário insere mais de um nome.
```bash
$ ./ola_usuario_2 Eu Mesmo
```
Ola Eu Mesmo  

(b) Se o usuário insere mais de um nome entre aspas duplas. Por exemplo:
```bash
$ ./ola_usuario_2 "Eu Mesmo"
```
Ola Eu Mesmo

(c) Se é usado um pipe. Por exemplo:
```bash
$ echo Eu | ./ola_usuario_2
```
Ola  

(d) Se é usado um pipe com mais de um nome. Por exemplo:
```bash
$ echo Eu Mesmo | ./ola_usuario_2
```
Ola

(e) Se é usado um pipe com mais de um nome entre aspas duplas. Por exemplo:
```bash
$ echo "Eu Mesmo" | ./ola_usuario_2
```
Ola

(f) Se é usado o redirecionamento de arquivo. Por exemplo:
```bash
$ echo Ola mundo cruel! > ola.txt
$ ./ola_usuario_2 < ola.txt
```
Ola

6. Crie um código em C que faz o mesmo que o código da questão 4, e em seguida imprime no terminal quantos valores de entrada foram fornecidos pelo usuário. Por exemplo, considerando que o código criado recebeu o nome de 'ola_usuario_3':

```bash
$ ./ola_usuario_3 Eu
$ Ola Eu
$ Numero de entradas = 2
```
```código
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
        printf("Ola ");
        for (int i = 1; i < argc; ++i)
        {
                printf("%s ", argv[i]);
        }
        printf("\n");
        printf("Número de entradas: %d\n", argc);
        return 0;

}

```
7. Crie um código em C que imprime todos os argumentos de entrada fornecidos pelo usuário. Por exemplo, considerando que o código criado recebeu o nome de 'ola_argumentos':

```bash
$ ./ola_argumentos Eu Mesmo e Minha Pessoa
$ Argumentos: Eu Mesmo e Minha Pessoa
```
```código
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
        printf("Argumentos:  ");
        for (int i = 1; i < argc; ++i)
        {
                printf("%s ", argv[i]);
        }
        printf("\n");
        return 0;

}

```
8. Crie uma função que retorna a quantidade de caracteres em uma string, usando o seguinte protótipo:
`int Num_Caracs(char *string);` Salve-a em um arquivo separado chamado 'num_caracs.c'. Salve o protótipo em um arquivo chamado 'num_caracs.h'. Compile 'num_caracs.c' para gerar o objeto 'num_caracs.o'.

```num_caracs.c
#include "num_caracs.h" 

int Num_Caracs(char *string){
        int i=0;
        char aux = 0;
        do{
                aux = string[i];
                i++;
        }while(aux != '\0');
        i--;
        return i;
} 
```

```num_caracs.h
int Num_Caracs(char *string);
```

9. Re-utilize o objeto criado na questão 8 para criar um código que imprime cada argumento de entrada e a quantidade de caracteres de cada um desses argumentos. Por exemplo, considerando que o código criado recebeu o nome de 'ola_num_caracs_1':

```bash
$ ./ola_num_caracs_1 Eu Mesmo
$ Argumento: ./ola_num_caracs_1 / Numero de caracteres: 18
$ Argumento: Eu / Numero de caracteres: 2
$ Argumento: Mesmo / Numero de caracteres: 5
```
```06_main.c
#include <stdio.h>
#include <stdlib.h>
#include "num_caracs.h"

int main(int argc, char *argv[]){
        int aux = 0;
        for (int i = 0; i < argc; ++i)
        {       
                aux = Num_Caracs(argv[i]);
            printf("Argumento: %s / Número de caracteres: %d\n", argv[i], aux);
        }
        printf("\n");
        return 0;

}
```

10. Crie um Makefile para a questão anterior.

```Makefile
num_caracs: 06_main.o num_caracs.o
        gcc $(CFLAGS) -o num_caracs 06_main.o num_caracs.o
06_main.o: 06_main.c num_caracs.h
        gcc $(CFLAGS) -c 06_main.c
num_caracs.o: num_caracs.c num_caracs.h
        gcc $(CFLAGS) -c num_caracs.c
clean:
        rm -f *.o num_caracs
```

11. Re-utilize o objeto criado na questão 8 para criar um código que imprime o total de caracteres nos argumentos de entrada. Por exemplo, considerando que o código criado recebeu o nome de 'ola_num_caracs_2':

```bash
$ ./ola_num_caracs_2 Eu Mesmo
$ Total de caracteres de entrada: 25
```

```07_main.c
#include <stdio.h>
#include <stdlib.h>
#include "num_caracs.h"

int main(int argc, char *argv[]){
        int Soma = 0, aux = 0;
        for (int i = 0; i < argc; ++i)
        {       
                aux = Num_Caracs(argv[i]);
                Soma += aux;
        }
        printf("Total de caracteres de entrada: %d\n", Soma);
        return 0;
}
```

12. Crie um Makefile para a questão anterior.

```Makefile
num_caracs: 07_main.o num_caracs.o
        gcc $(CFLAGS) -o num_caracs 07_main.o num_caracs.o
07_main.o: 07_main.c num_caracs.h
        gcc $(CFLAGS) -c 07_main.c
num_caracs.o: num_caracs.c num_caracs.h
        gcc $(CFLAGS) -c num_caracs.c
clean:
        rm -f *.o num_caracs
```
