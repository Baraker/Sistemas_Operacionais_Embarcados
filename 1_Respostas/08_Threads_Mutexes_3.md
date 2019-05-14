 1. Apresente as características e utilidades das seguintes funções:

(a) `popen()`
  
Esta é uma função que realiza a abertura de um processo através da criação de uma pipe, realização de um fork e chamada do shell. A função
deve especificar se a operação é de leitura (r) ou de escrita (w) em seu segundo argumento, valendo a adicição da letra 'e' para fechar o processo após sua conclusão. Ademais, em seu primeiro argumento deve  conter uma string termianda em NULL com um comando do shell.

(b) `pclose()`

Esta função vigia um processo até o seu término e retorna o seu valor de retorno.

(c) `fileno()`

2. Quais são as vantagens e desvantagens em utilizar:

(a) `popen()?`

Sua vantagem é a chamada paralela de um processo, uma vez que realiza o fork e uma execução de um comando shell. Porém, não possibilita com a mesma facilidade do fork e exec realizar outras operações dentro do código C antes da execução do código shell.

(b) `exec()?`

Considerando sua utilização aliada ao fork, a sua maior vantagem é a maior segurança quanto a integridade do código perante as incertezas do sistema operacional. 