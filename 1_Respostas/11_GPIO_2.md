1. Defina qual modelo de Raspberry Pi você utilizará no projeto desta disciplina com o Raspberry Pi. Justifique sua escolha.

O modelo que eu utilizarei para disciplina é o Raspberry Pi 3B+. A escolha se deve ao fato que um integrante do meu grupo comprou 
esta verção mais completa para utilizar na matéria e em projetos futuros, então nós utilizaremos este modelo por questões financeiras. Cabe destacar, que o poder de processamento da placa é o maior disponível e vem de encontro à aplicação de streaming que utilizaremos. 

2. Defina qual sistema operacional você utilizará no projeto desta disciplina com o Raspberry Pi. Justifique sua escolha.

O sistema operacioanal que utilizarei durante o desenvolvimento do projeto até o ponto de controle 4 é o Raspibian, ao final o grupo tentará mudar para um sistema operacional baseado no Arch Linux com o objetivo trazer um ambiente mais leve e que permita otimizar o sistema como um todo, porém não e uma garantia por conta da compatibildiade dos programas que utilizaremos ao longo do projeto. 

3. Defina de qual forma você instalará o sistema operacional escolhido. Escreva o passo-a-passo da instalação e forneça os links necessários para isto.

links: 	https://www.raspberrypi.org/downloads/
		https://www.raspberrypi.org/downloads/raspbian/
		https://www.raspberrypi.org/documentation/installation/installing-images/README.md

Estes dois links ensinam de forma clara a instalação do Raspibian.

De forma resumida, o primeiro passo e baixar a imagem do raspibian no segundo link, o segundo é formatar um cartão SD e então gravar a imagem no seu disco, o terceiro é adicionar um arquivo ssh dentro da imagem para utilizar o acesso remoto, e o quarto é realizar as configurações já dentro do sistema.

4. Defina de qual forma você desenvolverá software para o Raspberry Pi no projeto desta disciplina. Escreva o passo-a-passo do desenvolvimento e forneça os links necessários para isto.

A forma que eu utilizarei é:

1°: Escrita dos códigos pelo Sublime ainda no meu computador (Ubuntu 19.04);
2°: Acesso por ssh à raspberry;
3°: Envio dos arquivos pelo comando scp para a raspberry pelo bash do Ubuntu;
4°: Compilação, execução e validação dos arquivos pela raspberry;
5°: Caso aconteção erros simples a correção será feita pelo visualizador de arquivos 'vi' pela raspberry;
6°: Envio dos arquivos corretos para o Ubuntu e upload dos mesmos para o Github.