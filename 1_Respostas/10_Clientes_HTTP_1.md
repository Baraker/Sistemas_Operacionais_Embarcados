1. Especifique algumas portas importantes pré-definidas para o protocolo TCP/IP.

Porta	Serviço ou Aplicativo
21	FTP
23	Telnet
25	SMTP
53	DNS (Nome do domínio do Sistema)
63	Whois
70	Gopher
79	Finger
80	HTTP
110	POP3
119	NNTP

2. Com relação a endereços IP, responda:

(a) Qual é a diferença entre endereços IP externos e locais?

Os indereços locais são apenas utilizados 

(b) Como endereços IP externos são definidos? Quem os define?

Os endereços IP externos são definidos por um conjunto de 4 numeros inteiros totalizando 4 bytes e descrevem o identificador de rede e o identificador do hóspede. É o ICANN (Internet Corporation for Assigned Names and Numbers) que se encarrega de atribuir endereços IP públicos, ou seja, os endereços IP dos computadores diretamente ligados à rede pública da Internet.

(c) Como endereços IP locais são definidos? Quem os define?

o ICANN reservou um punhado de endereços em cada classe para atribuir um endereço IP aos computadores de uma rede local conectada à Internet sem correr o risco de criar uma confusão de endereços IP na rede das redes. Trata-se dos seguintes endereços: 

Endereços IP privados de classe A: 10.0.0.1 a 10.255.255.254, permitindo a criação de grandes redes privadas que compreendem milhares de computadores. 

Endereços IP privados de classe B: 172.16.0.1 a 172.31.255.254, permitindo criar redes privadas de média dimensão.


Endereços IP privados de classe C: 192.168.0.1 a 192.168.0.254, para a instalação de pequenas redes privadas. 

(d) O que é o DNS? Para que ele serve?

O sistema chamado DNS - Domain Name System permite associar nomes em linguagem corrente aos endereços numéricos. Chama-se resolução de nomes de domínios (ou resolução de endereços) a correlação entre os endereços IP e o nome de domínio associado.
Basicamente então esse sistema atribui nomes literais às maquinas.

3. Com relação à pilha de protocolos TCP/IP, responda:

(a) O que são suas camadas? Para que servem?

Para poder aplicar o modelo TCP/IP em qualquer máquina, ou seja, independentemente do sistema operacional, o sistema de protocolos TCP/IP foi decomposto em vários módulos que efetuam cada tarefa específica. Além disso, estes módulos executam estas tarefas umas após as outras em uma ordem determinada, resultando em um sistema estratificado. Esta , é a razão de o chamarmos de modelo em camadas. 

O termo camada é utilizado para evocar o fato que os dados que transitam na rede atravessam vários níveis de protocolos. Assim, os dados (pacotes de informações) que circulam na rede são tratados por cada camada, sucessivamente, acrescentando um elemento de informação (chamado 'cabeçalho') e, em seguida, transmitindo à camada seguinte.

O objetivo de um sistema em camadas é separar o problema em partes diferentes de acordo com o seu nível de abstração. Cada camada do modelo se comunica com uma camada adjacente (a de cima ou a de baixo). Cada camada utiliza, assim, os serviços das camadas inferiores e fornece os seus serviços às do nível superior.

(b) Quais são as camadas existentes? Para que servem?

Os principais protocolos da TCP/IP são: Camada de Aplicação (TCP ou UDP), Camada de Internet (IP, ARP, RARP), Camada de Acesso à rede (FDDI, PPP, Ethernet, Anéis de ficha à jeton (Token ring)), Camada de Transporte e Camada Físico.

A camada de Acesso à rede especifica a forma que os dados devem ser encaminhados independentemente do tipo de rede utilizado, a camada da Internet é encarregada fornecer o pacote de dados (datagrama), a camada do Transporte garante o encaminhamento dos dados, assim como os mecanismos que permitem conhecer o estado da transmissão e a camada de aplicação agrupa os a padrão da rede (Telnet, SMTP, FTP,etc.).

(c) Quais camadas são utilizadas pela biblioteca de sockets?

Considerando a Internet e o TCP/IP, os sockets estão entre a camada de transporte e a de aplicações. Estando nesse ponto de intercessão, eles conseguem fazer uma interface entre a aplicação e rede de maneira bem transparente.

(d) As portas usadas por servidores na função bind() se referem a qual camada?

Se referem à camada de aplicação.

(e) Os endereços usados por clientes na função connect() se referem a qual camada?



4. Qual é a diferença entre os métodos `GET` e `POST` no protocolo HTTP?

Comando		Descrição
GET			Pedido do recurso situado no URL especificado
HEAD		Pedido do cabeçalho do recurso situado no URL especificado
POST		Envio de dados ao programa situado no URL especificado
PUT			Envio de dados ao URL especificado
DELETE		Remoção do recurso situado no URL especificado