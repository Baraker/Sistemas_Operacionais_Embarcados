1. Com relação às conexões GPIO do modelo de Raspberry Pi que você usará no projeto, responda:

(a) Quais pinos podem ser utilizados como entradas e saídas digitais comuns?

Para a raspberry pi 3B+ serão os pinos:

GPIO 4, 5, 6, 12, 13, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 e 26

(b) Quais pinos possuem resistores de pull-up e pull-down?

Todos os pinos podem configurar resistores de pull-up ou pull-down.

(c) Quais formas de comunicação serial são suportados pelos pinos GPIO?

SPI, I2C e UART

2. Apresente outras 3 bibliotecas de acesso I/O em C para o Raspberry Pi.

gpio_dev_mem.h, esta biblioteca atua diretamente com escrita em memória para realizar operações no GPIO.

gpio_sysfs.h, esta biblioteca atua com a escrita no arquivos destinados ao GPIO em '/sys/class/gpio/' e por tanto consegue habilitar, setar como in/out, escrever, etc.

WiringPi é uma bilioteca desenvolvida para o Raspibian 32-bit para a utilização do GPIO e pode ser instalada e utilizada com facilidade.
