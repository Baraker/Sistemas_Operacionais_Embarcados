1. Apresente 5 sistemas operacionais suportados pelo Raspberry Pi, e algumas de suas características.
  
Raspibian: 
  
Raspibian é o OS oficial desenvolvido pela Raspberri Pi e que tem ao longo dos anos recebido diversas customizações
e facilidade. Ele possui como características a instalação facilitada pelo Software NOOBS, consegue realizar boot 
através de uma conexão Ethernet, possui grande compatilidade para executar aplicativos e dificilmente apresenta bugs
e possui um bom leitor de pdf chamado qpdfview.
  
OSMC:  
  
OSMC é uma distribuição Linux embarcada, minimalistica e que se atulizada automaticamente que oferece uma plataforma front-end para diversos dispositivos. OSMC é um sistema operacional fácil de utilizar. Ele é baseado em Debian, o que signigica que tem a sua disposição mais de 30.000 pacotes disponíveis no seus repositório. É de fácil e rápida instalação, e possui atualizações com frequência. 
  
OpenELEC:  
  
OpenELEC provê um software com uma central completa de mídia que acompanha uma verção pre-configurada do Kodi e vários codecs para
video games retrô e emuladores. Ele é extremamente pequeno e realiza seu boot com grande rapidez.
  
RISC OS:  
  
RISC OS /rɪskoʊˈɛs/[4] is a computer operating system originally designed by Acorn Computers Ltd in Cambridge, England. First released in 1987, it was specifically designed to run on the ARM chipset, which Acorn had designed concurrently for use in its new line of Archimedes personal computers. RISC OS takes its name from the RISC (reduced instruction set computing) architecture supported.
  
RISC OS é um sistema operacional originalmente desenvolvido para ser utilizado em processadores ARM. RISC OS, vem da arquitetura RISC
e portanto possui suporte para ela. Seu sistema ocupa apenas de 4 a 5 MB de memória ROM e possui a vantagem da cooperative multitasking.
  
Windows IoT Core:
  
Windows 10 IoT é um membro da família Windows 10 que traz a capacidade de classe empresarial, segurança e capacidade de gerenciamento para a Internet das coisas. Este sistema é uma grande alternativa para implementação de um dispositivo habilitado para voz por conta da compatibilidade com a Cortano SDK. Possui também um sistema de segurança mais forte e trás o Shell do Windows.
  
2. Apresente as formas de instalação de sistemas operacionais para o Raspberry Pi.

Existem duas principais formas de intalação de sistemas operacionais para o raspberry pi. A primeira utiliza
o software noobs que realizar grande parte da configuração para o usuário e a segunda é o dowmload do arquivo
de imagem do sistema operacional e em seguida a sua gravação em SD card.

3. Apresente 3 formas de desenvolvimento de software para o Raspberry Pi.

Primeira forma: Escrever os códigos no Sublime pelo computador e enviar os arquivos para o raspberry pelo comando scp para validação.
Segunda forma: 	Escrever os códigos no vi pela raspberry com acesso remoto por ssh e executar os códigos para validação.
Terceira forma:	Escrever os códigos no sublime pelo computador os compilar para ARM e enviar os executáveis para a raspberry para validação.

4. Apresente 3 formas de acesso remoto ao Raspberry Pi.

A primeira forma é utilizar o comando ssh dado o nome do dispositivo e o seu IP, o ambiente de utilização da raspberry torna-se então o
terminal do OS que chamou o comando.

A segunda é utilizar o promgrama Putty que nada mais é que o ssh mas que abre uma janela de comunicação com a raspberry e possui outras opções de customização.

A terceira opção é utilizar o VNC viewer, que permitirá acessar o ambiente gráfico do OS instalado na raspberry. É preciso baixar o programa no OS do computador e na raspberry, além de habilitar sua uitlização nas configurações.

5. Apresente as formas possíveis de compilação de código em C para o Raspberry Pi.

É possível compilar o código dentro da raspberry ou no computador, porém ao compilar no computador é preciso utilizar a forma de compilação correta de acordo com o processador da Raspberry (ARM).

6. Apresente as formas possíveis de compilação de código em Python para o Raspberry Pi.

Vale a mesma regra para os códigos em python.













