1. Quais são as vantagens e desvantagens em utilizar:

(a) fork?
```txt
A função fork possui como principal vantagem a proteção dos dados referente a corrupção por concorrência de atribuições, pois os processos são independetens mesmo que suas variáveis tenham mesmo nome, por exemplo. Entretanto, a comunicação entre os processos pode ser considerada com pesada quando comparada com a comunicação das threads, por que quando usamos a função fork precisamos criar os canais chamados pipes que atuam sob comunicação FIFO e para que o código consiga se organizar o programador precisa desenvolver métodos de temporarização.
```

(b) threads?
```txt
A utilização de threds é vantajosa pois a comunicação entre as execuções de código tornam-se mais fáceis; a organização das threads é mais simples por conta pelas funções de chaveamento (MUTEX), cancelamento e espera. Entretanto, como as linhas de execução compartilham o mesmo espaço de memória, torna-se factível a corrupção de dados pela concorrência e o programa não consegue resultados corretos. Ademais, quando se utiliza o MUTEX, o mau gerenciamento das chaves pode gerar Deadlocks que são condições em que o código simplesmente para a sua execução pois todas as threads estão bloqueadas.
```

2. Quantas threads serão criadas após as linhas de código a seguir? Quantas coexistirão? Por quê?

(a)

```C
void* funcao_thread_1(void *arg);
void* funcao_thread_2(void *arg);

int main (int argc, char** argv)
{
	pthread_t t1, t2;
	pthread_create(&t1, NULL, funcao_thread_1, NULL);
	pthread_create(&t2, NULL, funcao_thread_2, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
```
```txt
Serão criadas três threads, e as três possivelmente coexistiram, pois quando a função "pthread_create" é chamada a thread principal continua sua execução normalmente e chama a outra thread em seguida. Não é possível, assegurar 100% que irão coexistir pois depende da função que elas executam e da preferência de execução do sistema operacional que as executa assíncronamente.
```


(b)
```C
void* funcao_thread_1(void *arg);
void* funcao_thread_2(void *arg);

int main (int argc, char** argv)
{
	pthread_t t1, t2;
	pthread_create(&t1, NULL, funcao_thread_1, NULL);
	pthread_join(t1, NULL);
	pthread_create(&t2, NULL, funcao_thread_2, NULL);
	pthread_join(t2, NULL);
	return 0;
}
```
```txt
Serão criadas duas threads, a principal, a thread que atuará na função1 e posteriormente a thread que atuará na função 2. Elas não coexistirão conforme a função "pthread_join" força o código esperar o término da execução da thread que chama a função 1. Assim, nenhuma thread coexistirá, enquanto uma executa as outras estão bloqueadas ou ainda não foram criadas. 
```

3. Apresente as características e utilidades das seguintes funções:

(a) `pthread_setcancelstate()`

```txt
Esta função determina se um thread pode ser cancelada ou não de forma que inicialmente todas as threads podem ser canceladas, inclusive a thread inicial. Se uma thread não pode ser cancelada ela o pedido de cancelamento é bloqueado até o momento que a thread receber a permissão para ser cancelável.
```

(b) `pthread_setcanceltype()`

```txt
Esta função, diferentemente da anterior, determina como o cancelamento deve ocorrer e são de duas formas:

	- Deffered: o pedido de cancelamento é despachado para a thread e só é executado quando a thread chama uma função que resulta em um ponto de cancelamento.

	- Asynchronous: a thread poderá ser cancelada a qualquer momento e normamente acontece no ato do pedido, mas o sistema não pode garantir isto.
```

(DICA: elas são relacionadas à função pthread_cancel().)
