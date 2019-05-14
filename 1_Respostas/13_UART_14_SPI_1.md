1. Cite as vantagens e desvantagens das comunicação serial:

(a) Assíncrona (UART).

Este protocolo de comunicação possui como maior vantagem a autonomia dos dispositivos para mandar dados a qualquer momento sem precisar
de requisições para que o protocolo funcione. Possui métodos para verificação de erro por bit de paridade, método de endereçamento de dispositivos e método para atulizar a sincronia para sistemas mais lentos. Entretanto por ser assíncrono possui limitações de velocidade de transmissão e passa a depeder de dois osciladores do mestre e dos escravos.

(b) SPI.

O protocolo SPI tem como principal característica ser full-duplex, uma vez que os dados do mestre e dos escravos estão em descolamento circular. Dessa maneira, consegue resultados interessantes para sistemas de escravos síncronos, pois consegue economizar pinos e realizar o trafego da informação. É possível também trabalhar com seletoras para cada escravo e realizar deslocamentos de informação apenas com 1 mestre e 1 escravo. A dependência dos osciladores e menos como o clock do mestre é passado para os escravos. Porém, é possível perceber que este protocolo necessita de vários ciclos de clock para levar a informação para um determinado dispositivo caso esteja em Daisy Chain. Ademais o deslocamento circular da informação muitas vezes não é necessário.

2. Considere o caso em que a Raspberry Pi deve receber leituras analógico/digitais de um MSP430, e que a comunicação entre os dois é UART. É tecnicamente possível que o MSP430 mande os resultados da conversão A/D a qualquer hora, ou ele deve aguardar a Raspberry Pi fazer um pedido ao MSP430? Por quê?

É possível sim, pois a comunicação UART é assíncrona e, portanto, está sempre vigiando o bit que determina o início da transmissão de dados.

3. Considere o caso em que a Raspberry Pi deve receber leituras analógico/digitais de um MSP430, que a comunicação entre os dois seja SPI, e que o MSP430 seja o escravo. É tecnicamente possível que o MSP430 mande os resultados da conversão A/D a qualquer hora, ou ele deve aguardar a Raspberry Pi fazer um pedido ao MSP430? Por quê?

Não é possível, pois a MSP430 possui dependência de clock da Raspberry Pi no caso da comunicação SPI e sua informação só é transmitida à Raspberry quando esta realiza o deslocamento da informação e informa à MSP430 que quer as converções A/D. 

4. Se o Raspberry Pi tiver de se comunicar com dois dispositivos via UART, como executar a comunicação com o segundo dispositivo?

Para este problema é possível habilitar o bit de endereçamento dos dispositivos receptores com: UCMODEx = 10, então é possível indicar qual dispositivo deve 'ouvir' aquela determinada informação.

5. Se o Raspberry Pi tiver de se comunicar com dois dispositivos via SPI, como executar a comunicação com o segundo dispositivo?

Existem duas formas:

Seleção Individual - Nesta configuração haverá um canal de dados de seleção para cada um dos dispositivos e a passagem da informação então ocorre entre o mestre o segundo dispositivo escravo diretamente, é possível transmitir para o primeiro ou para os dois caso necessário.

Daisy Chain - Já desta forma a informação é passada de forma colaborativa e circular entre os dispositivos, então para isso estes, inicialmente, precisam tratar a informação de forma síncrona. Portanto, para a comunicação acontecer com o segundo dispositivo o sistema precisará de um tempo maior até que a informação passe pelo primeiro dispositivo.