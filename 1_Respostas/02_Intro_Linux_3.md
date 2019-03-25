Para todas as questões, escreva os scripts e as chamadas correspondentes no terminal.

1. Crie um arquivo com nome _teste1.txt_, e escreva nele o texto "Número do arquivo = 1". Repita o procedimento para os arquivos _teste2.txt_, _teste3.txt_, ..., _teste100.txt_, escrevendo o texto correspondente para cada um deles ("Número do arquivo = 2", "Número do arquivo = 3", ..., "Número do arquivo = 100").
  
$ echo '#!/bin/bash' > teste.sh  
$ chmod 755 teste.sh  
  
#!/bin/bash
for i in {1..100}  
do  
 echo  Número do arquivo = $i > _teste$i.txt  
done  
  
$ ./teste.sh
  
  
2. Faça um script chamado _cals.sh_ que apresente o calendário de vários meses indicados pelo usuário, usando o seguinte formato:  
  
```script
./cals.sh MES1 ANO1 MES2 ANO2 MES3 ANO3  
```
  
Não limite o script a 3 meses. Ele deve funcionar para vários casos, como por exemplo:  
  
```script  
./cals.sh 1 2020  
./cals.sh 1 2019 2 2020 3 2021 1 2010  
```  
$ echo '#!/bin/bash' > _cals.sh  
$ chmod 755 _cals.sh  

#!/bin/bash  
n=0  
args=""  
  
for i in $@  
do  
  
	if [ $n -eq 0 ]; then  
		args=$i  
		n=1  
	elif [ $n -eq 1 ]; then  
		cal $args $i  
		n=0  
	fi  
  
done   
  
$ ./_cals.sh  
  
  
3. Utilizando a lógica do script anterior, descubra em que dia da semana caiu o seu aniversário nos últimos dez anos.  
  
$ ./_cal.sh 10 2019 10 2018 10 2017 10 2016 10 2015 10 2014 10 2013 10 2012 10 2011 10 2010  
  
ou o código:  

$ echo '#!/bin/bash' > Bdate.sh  
$ chmod 755 Bdate.sh  
  
  
#!/bin/bash  
n=0  
args1=""  
args2=""  
  
for i in $@  
do  
  
	if [ $n -eq 0 ]; then  
		args1=$i  
		n=1  
	elif [ $n -eq 1 ]; then  
		args2=$i  
		n=2  
	elif [ $n -eq 2 ]; then  
		date -d $args1/$args2/$i  
		n=0  
	fi  
  
done  
  
$ ./_Bdate.sh 10 04 2019 10 04 2018 10 04 2017 10 04 2016 10 04 2015 10 04 2014 10 04 2013 10 04 2012 10 04 2011 10 04 2010  
  
4. Crie um arquivo _sites.txt_ com o seguinte conteúdo:  

```  
https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/raw/master/Aulas/01_Linux%20b%C3%A1sico.pdf  
https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/raw/master/Aulas/01_Linux%20b%C3%A1sico_Shell_Script.pdf  
https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/raw/master/Aulas/01_Sistemas%20Embarcados%20-%20Aula%201%20-%20Introdu%C3%A7%C3%A3o.pdf  
```  
  
Estes são links para slides de 3 aulas desta dsciplina, um para cada linha do arquivo _sites.txt_. Faça um script que faz o download destes slides automaticamente, a partir do arquivo _sites.txt_. (DICA: use o comando wget.)  


$ echo '#!/bin/bash' > _sites.sh  
$ chmod 755 _sites.sh  

#!/bin/bash

wget https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/raw/master/Aulas/01_Linux%20b%C3%A1sico.pdf
wget https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/raw/master/Aulas/01_Linux%20b%C3%A1sico_Shell_Script.pdf
wget https://github.com/DiogoCaetanoGarcia/Sistemas_Embarcados/raw/master/Aulas/01_Sistemas%20Embarcados%20-%20Aula%201%20-%20Introdu%C3%A7%C3%A3o.pdf
  
$ ./_sites.sh
  
5. Faça um script chamado _up.sh_ que sobe _N_ níveis na pasta onde você estiver, usando $1 como parâmetro de entrada. Por exemplo, se você estiver em **/home/aluno/Documents** e executar **./up.sh 2**, você automaticamente vai para a pasta **/home**.
  
$ echo '#!/bin/bash' > _up.sh  
$ chmod 755 _up.sh  
  
for i in $#  
do  
	cd ..
done 