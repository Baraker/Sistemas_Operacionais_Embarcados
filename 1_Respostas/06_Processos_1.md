1. Como se utiliza o comando `ps` para:

(a) Mostrar todos os processos rodando na máquina?

```bash
ps -a  
```

(b) Mostrar os processos de um usuário?
  
nome do usuário: abhay  

```bash
ps -auabhay  
```

(c) Ordenar todos os processos de acordo com o uso da CPU?

```bash
  ps uax --sort %cpu  
```

(d) Mostrar a quanto tempo cada processo está rodando?

```bash
ps -eo pid,etime
```

2. De onde vem o nome `fork()`?

O} nome fork vem de bifurcação.

3. Quais são as vantagens e desvantagens em utilizar:

(a) `system()`?
  
system tem como vantagem a simplicidade na execução de comandos dentro de programas e por ocnta de automaticamente criar um processo filho, porém esta função depende muito do sistema e pode criar brechas e falhas com facilidade.  
  
(b) `fork()` e `exec()`?

tanto fork quanto exec, não conseguem criar e executar um processo em um único passo, mas estes utilizados juntamente são poderosos uma vez qeu o fork duplica o processo corrente e o novo processo recebe um novo PID e por consequência é um processo totalemnte diferente que é execuatado normalmente assim como o processo original. Ambos podem ser diferenciados, o processo pai e filho. A função exec vai cessar imediatamente a execução do processo corrente e passa a executar um novo programa do início. Assim, ambos podem ser utilizados em conjunto para realizar tarefas simultâneas com cláusulas condicionais.

4. É possível utilizar o `exec()` sem executar o `fork()` antes?

Sim é possível, porém não é recomendável pois o processo corrente pode ser importante e o exec irá cessar sua execução, já com o fork os dois podem ser executados idependentemente.   

5. Quais são as características básicas das seguintes funções:

(a) `execp()`?	aceitam endereço relativo, 

(b) `execv()`?	aceitam apenas endereço completo do programa, aceitam que sua lista de argumentos seja nula, 

(c) `exece()`?	aceitam apenas endereço completo do programa, aceitam argumento adicional

(d) `execvp()`?	aceitam endereço relativo, aceitam que sua lista de argumentos seja nula  

(e) `execve()`?	aceitam apenas endereço completo do programa, aceitam que sua lista de argumentos seja nula, aceitam argumento adicional  

(f) `execle()`?	aceitam apenas endereço completo do programa, aceitam argumentos de entrada args, aceitam argumento adicional  
