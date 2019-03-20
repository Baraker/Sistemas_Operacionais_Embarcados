1 - Por que o Linux recebeu esse nome?

Linux é uma junção do nome do principal criador do sistema, Linus Torvalds, e com UNIX. Anteriormente, o sistema se chamaria Freax, mas um dos administradores nomeou o projeto como Linux e com o tem Torvalds consentiu o nome.

2 - O que são daemons?

Daemons são ferramentas de controle de sistema que estão incorporadas no Linux e que fazem tarefas como inicar, reiniciar, parar, etc. Eles estão acima das execuções em geral e dessa maneira tem controle sobre elas. Daemons possuem a função de manter o bom funcionamento e organização do sistema e são geralmente iniciados no boot.

3 - O que é o shell?

Pode ser definido como um ambiente de comunicação entre o usuário e o Kernel que traduz os comandos do usuário para o Kernel para então realizar tarefas.

4 - Por que é importante evitar executar o terminal como super-usuário?

A utilização do sudo no terminal do Linux resulta na não verificação do gravidade do comando, ou seja, o sistema não irá confirmar se o usuário realmente quer executar. O comando rm é um exemplo, pois pode apagar arquivos importantes e não oferecer maneiras de recuperá-los, assim tem capacidade de danificar o sistema.

5 - Qual botão do teclado completa o que o usuário escreve no terminal, de acordo com o contexto?

O botão que completa o que o usuário escreve no terminal de acordo com o texto é o Tab.

6 - Quais botões do teclado apresentam instruções escritas anteriormente?

A setas para cima e para baixo conseguem acessar um histórico de comandos escritos anteriormente.

7 - Apresente os respectivos comandos no terminal para: 

(a) Obter mais informações sobre um comando. 
	comando: man
	exemplo: man mv

(b) Apresentar uma lista com os arquivos dentro de uma pasta. 
	comando: ls
	exemplo: ls -la

(c) Apresentar o caminho completo da pasta. 
	comando: pwd
	exemplo:

(d) Trocar de pasta. 
	comando: cd
	exemplo: cd ~ ; cd ..

(e) Criar uma pasta. 
	comando: mkdir
	exemplo: mkdir teste

(f) Apagar arquivos definitivamente. 
	comando: rm
	exemplo: rm teste.txt

(g) Apagar pastas definitivamente. 
	comando: rm
	exemplo: rm -R teste

(h) Copiar arquivos. 
	comando: cp
	exemplo: cp teste.txt ~/Imagens

(i) Copiar pastas. 
	comando: cp -r
	exemplo: cp ~/Documentos/Faculdade/Fotos ~/Imagens

(j) Mover arquivos. 
	comando: mv
	exemplo: mv teste.txt ~/Imagens

(k) Mover pastas. 
	comando: mv
	exemplo: mv ~/Documentos/Faculdade/Fotos ~/Imagens

(l) Renomear pastas. 
	comando: mv
	exemplo: mv minha_vida minha_vida2

(m) Apresentar o conteúdo de um arquivo. 
	comando: cat
	exemplo: cat teste.txt

(n) Apresentar o tipo de um arquivo. 
	comando: file
	exemplo: file teste.txt

(o) Limpar a tela do terminal.
	comando: clear; Ctrl + L
	exemplo: 

(p) Encontrar ocorrências de palavras-chave em um arquivo-texto. 
	comando: grep
	exemplo: grep "palavra" 02_Intro_Linux_1.md

(q) Ordenar informações em um arquivo-texto. 
	comando:
	exemplo:

(r) Substituir ocorrências de palavras-chave em um arquivo-texto. 
	comando:
	exemplo:

(s) Conferir se dois arquivos são iguais. 
	comando:
	exemplo:

(t) Escrever algo na tela.
	comando: cat + grep
	exemplo: cat teste.txt | grep "palavra"

