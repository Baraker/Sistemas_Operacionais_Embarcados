1. Com relação ao modelo cliente-servidor, responda:

(a) Quais são as características básicas deste modelo?

Este modelo possui duas partes o cliente e o servidor que são conectados com uma espécie de pipe chamada socket e podem ter duas configurações/protocolos Stream (TCP - Transmission Control Protocol) ou Datagram (UDP - User Datagram Protocol). Dentro de uma desssa configurações as partes conseguem trocar informações.

(b) Quais são as características básicas do servidor?

Os servidores são abientes de processamentos ou de armazenamento de dados. Ambos de protocolo TCP e UDP precisam ser credenciados com com endereços locais de IP e número de porta de protocolo. Porém, para a configuração TCP é preciso ainda configurá-lo como passivo e submisso às requisições de clientes e então as requisições de conexão devem ser aceitas com a criação de um novo socket para a tranmissão de dados que ao final é fechado.

(c) Quais são as características básicas do cliente?

Os clientes são plataformas que comunicam com o servidor de forma direta e precisam estar configurados corretamente e serem aceitos pelo servidor.

2.  Com relação ao protocolo de comunicação da internet, responda:
  
(a) O que são protocolos de comunicação?
  
Protocolos de comunicação são métodos para transferência de dados entre um cliente e um servidor.

(b) Quais são as características básicas de protocolos de comunicação?

Suas características básicas advém do modelo cliente servidor, por tanto possuem um estágio de criação e configuração e um outro para transmissão de dados. 

3. Com relação ao protocolo TCP, responda:

(a) O que são portas no protocolo TCP?

As portas são valores de 16 bits unsigned binary numbers com range de 1 a 65535, vale lembrar que 0 é reservado.

(b) Para que servem estas portas?

As portas no protocolo TCP correspodem ao lote da casa dada uma rua, então dado um endereço de internet (IP) a porta será relativa a este endereço e proporcionará a comunicação ao servidor correto.