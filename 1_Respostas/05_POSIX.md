Para todas as questões, utilize as funções da biblioteca `stdio.h` de leitura e de escrita em arquivo (`fopen()`, `fclose()`, `fwrite()`, `fread()`, dentre outras). Compile os códigos com o gcc e execute-os via terminal.

1. Crie um código em C para escrever "Ola mundo!" em um arquivo chamado 'ola_mundo.txt'.
```c
#include <stdio.h>  // Para a funcao printf()
#include <fcntl.h>  // Para a funcao open()
#include <unistd.h> // Para a funcao close()
#include <stdlib.h> // Para a função exit()

int main(int argc, const char * argv[]) {
  int fp;
  char string[] = "Ola mundo!";
  int i, n;
  fp = open("ola_mundo.txt",O_WRONLY| O_CREAT, S_IRWXU);
  if(fp == -1)
  {
    /* Arquivo ASCII, para escrita */
    printf( "Erro na abertura do arquivo");
    exit(-1);
  }
  for(i=0; string[i]; i++)
    write(fp, &(string[i]), 1); // Grava a string, caractere a caractere  
  write(fp, "\n", 1);
  close(fp);
  return 0;
}

```
2. Crie um código em C que pergunta ao usuário seu nome e sua idade, e escreve este conteúdo em um arquivo com o seu nome e extensão '.txt'. Por exemplo, considerando que o código criado recebeu o nome de 'ola_usuario_1':

```bash
$ ./ola_usuario_1
$ Digite o seu nome: Eu
$ Digite a sua idade: 30
$ cat Eu.txt
$ Nome: Eu
$ Idade: 30 anos
```
```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void DMscan(char * string);
void file_print(char * string, int fp);

int main(int argc, const char * argv[]) {
  
	int fp;
	char aux = 0;
	char *nome, *idade, *string;
	char aux_print[10];
	int i=0, n;

	nome = (char*)malloc(sizeof(char));
	idade = (char*)malloc(sizeof(char));

	printf("Digite o seu nome: ");
	DMscan(nome);

	printf("Digite a sua idade: ");
	DMscan(idade);

	n = strlen(nome);
	string = (char*)malloc(n*sizeof(char));
	strcpy(string, nome);
	strcat(string, ".txt");

	fp = open(string ,O_WRONLY| O_CREAT | O_APPEND, S_IRWXU);
	if(fp == -1)
    {
        printf("\nNao consigo abrir o arquivo ! ");
        exit(1); }

	strcpy(aux_print, "Nome: ");
	file_print(aux_print, fp);
	file_print(nome, fp);
	strcpy(aux_print, "\nIdade: ");
	file_print(aux_print, fp);
	file_print(idade, fp);
	strcpy(aux_print, "\n");
	file_print(aux_print, fp);
	
	free(nome);
	free(idade);
	free(string);
	close(fp);
	return 0;
}

void file_print(char * string, int fp){
	for(int i=0; string[i]; i++)
    	write(fp, &(string[i]), 1); // Grava a string, caractere a caractere  
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

3. Crie um código em C que recebe o nome do usuário e e sua idade como argumentos de entrada (usando as variáveis `argc` e `*argv[]`), e escreve este conteúdo em um arquivo com o seu nome e extensão '.txt'. Por exemplo, considerando que o código criado recebeu o nome de 'ola_usuario_2':

```bash
$ ./ola_usuario_2 Eu 30
$ cat Eu.txt
$ Nome: Eu
$ Idade: 30 anos
```
```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void file_print(char * string, int fp);

int main(int argc, const char * argv[]) {
  
	int fp;
	char aux = 0;
	char *nome, *idade, *string;
	char aux_print[10];
	int i=0, n, id;

	if (argc < 2)
	{
		printf("Insira Argumentos de Entrada!\n" );
		return 0;
	}

	n = strlen(argv[1]);
	id = strlen(argv[2]);

	nome = (char*)malloc(n*sizeof(char));
	idade = (char*)malloc(id*sizeof(char));
	string = (char*)malloc(n*sizeof(char));

	strcpy(nome, argv[1]);
	strcpy(idade, argv[2]);

	strcpy(string, argv[1]);
	strcat(string, ".txt");

	fp = open(string ,O_WRONLY| O_CREAT, S_IRWXU);
	if(fp == -1)
    {
        printf("\nNao consigo abrir o arquivo ! ");
        exit(1); }

	strcpy(aux_print, "Nome: ");
	file_print(aux_print, fp);
	file_print(nome, fp);
	strcpy(aux_print, "\nIdade: ");
	file_print(aux_print, fp);
	file_print(idade, fp);
	strcpy(aux_print, "\n");
	file_print(aux_print, fp);

	free(nome);
	free(idade);
	free(string);
	close(fp);
	return 0;
}

void file_print(char * string, int fp){
	for(int i=0; string[i]; i++)
    	write(fp, &(string[i]), 1); // Grava a string, caractere a caractere  
}
```

4. Crie uma função que retorna o tamanho de um arquivo, usando o seguinte protótipo: `int tam_arq_texto(char *nome_arquivo);` Salve esta função em um arquivo separado chamado 'bib_arqs.c'. Salve o protótipo em um arquivo chamado 'bib_arqs.h'. Compile 'bib_arqs.c' para gerar o objeto 'bib_arqs.o'.

5. Crie uma função que lê o conteúdo de um arquivo-texto e o guarda em uma string, usando o seguinte protótipo: `char* le_arq_texto(char *nome_arquivo);` Repare que o conteúdo do arquivo é armazenado em um vetor interno à função, e o endereço do vetor é retornado ao final. (Se você alocar este vetor dinamicamente, lembre-se de liberar a memória dele quando acabar o seu uso.) Salve esta função no mesmo arquivo da questão 4, chamado 'bib_arqs.c'. Salve o protótipo no arquivo 'bib_arqs.h'. Compile 'bib_arqs.c' novamente para gerar o objeto 'bib_arqs.o'.  

Respostas das questões 4 e 5:  

```c
int tam_arq_texto(char *nome_arquivo);
char* le_arq_texto(char *nome_arquivo);
```

```c
#include "bib_arqs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int tam_arq_texto(char *nome_arquivo){

	int p;
	int count = 0;
	char c;

	p = open(nome_arquivo ,O_RDONLY);
	if(p == -1)
    {
        printf("\nNao consigo abrir o arquivo ! ");
        exit(1); }

	while(read(p, &c, 1) != 0)
		count++;

	close(p);
	return(count);
} 

char* le_arq_texto(char *nome_arquivo){
	int p;
	char *texto;
	char c;
	int n = 0, i = 0;

	n = tam_arq_texto(nome_arquivo);
	texto = (char*)malloc(n*sizeof(char));

	p = open(nome_arquivo ,O_RDONLY);
	if(p == -1)
    {
        printf("\nNao consigo abrir o arquivo ! ");
        exit(1); }

	while(read(p, &c, 1) != 0)
	{
		if(c != '\0')
			texto[i] = c;
		i++;
	}
	close(p);
	return(texto);
}
```

6. Crie um código em C que copia a funcionalidade básica do comando `cat`: escrever o conteúdo de um arquivo-texto no terminal. Reaproveite as funções já criadas nas questões anteriores. Por exemplo, considerando que o código criado recebeu o nome de 'cat_falsificado':

```bash
$ echo Ola mundo cruel! Ola universo ingrato! > ola.txt
$ ./cat_falsificado ola.txt
$ Ola mundo cruel! Ola universo ingrato!
```


```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib_arqs.h"

int main(int argc, const char * argv[]) {

	char *text, *arquivo;
	int n;

	if (argc < 2)
	{
		printf("Insira Argumentos de Entrada!\n" );
		return 0;
	}

	n = strlen(argv[1]);
	arquivo = (char*)malloc(n*sizeof(char));
	strcpy(arquivo, argv[1]);

	text = le_arq_texto(arquivo);
	printf("%s", text);

	free(arquivo);
	free(text);
	return 0;

}
```

```bash
cat_falsificado: cat_falsificado.o bib_arqs.o
	gcc $(CFLAGS) -o cat_falsificado cat_falsificado.o bib_arqs.o
cat_falsificado.o: cat_falsificado.c bib_arqs.h
	gcc $(CFLAGS) -c cat_falsificado.c
bib_arqs.o: bib_arqs.c bib_arqs.h
	gcc $(CFLAGS) -c bib_arqs.c
clean:
	rm -f *.o cat_falsificado
```
7. Crie um código em C que conta a ocorrência de uma palavra-chave em um arquivo-texto, e escreve o resultado no terminal. Reaproveite as funções já criadas nas questões anteriores. Por exemplo, considerando que o código criado recebeu o nome de 'busca_e_conta':

```bash
$ echo Ola mundo cruel! Ola universo ingrato! > ola.txt
$ ./busca_e_conta Ola ola.txt
$ 'Ola' ocorre 2 vezes no arquivo 'ola.txt'.
```
Para esta tarefa, criei mais duas funções e adicionei na bib_arqs.c e escrevi uma nova função para as chamar corretamente e implementar a 'busca_e_conta':

Função principal:  
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib_arqs.h"

int main(int argc, const char * argv[]) {

	char *text, *arquivo, *word;
	int n, ocorrencias;

	if (argc < 2)
	{
		printf("Insira Argumentos de Entrada!\n" );
		return 0;
	}

	n = strlen(argv[1]);
	word = (char*)malloc(n*sizeof(char));
	strcpy(word, argv[1]);

	n = strlen(argv[2]);
	arquivo = (char*)malloc(n*sizeof(char));
	strcpy(arquivo, argv[2]);

	text = le_arq_texto(arquivo);
	ocorrencias = Search_and_count(text, word);

	printf("'%s' ocorre %d vezes no arquivo '%s'", word, ocorrencias, arquivo);

	free(arquivo);
	free(text);
	return 0;

}
```

Outras duas funções adicionadas:
```c
int Search_and_count(char *text, char *word) {

	char *token, *frag_data;
	int len_word, count = 0;

	len_word = strlen(word);

	frag_data = (char*)malloc(strlen(text)*sizeof(char));
	strcpy(frag_data, text);

	token = strtok(frag_data, " ");
	if (string_comp(token, word, len_word))
	{
		count++;
	}
	while(token != NULL){
		token = strtok(NULL, " ");
		if(token != NULL){
			if (string_comp(token, word, len_word))
			{
				count++;
			}
		}
	}

	free(token);
	free(frag_data);
	
	return count;
}
```

```c
int string_comp(char *str1, char *str2, int len_word){
	int flag = 1;
	for (int i = 0; i < len_word; ++i)
	{
		if(str1[i] != str2[i])
			flag = 0;
	}
	return flag;
}
```