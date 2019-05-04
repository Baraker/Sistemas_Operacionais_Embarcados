#!/bin/bash  
'
	
	Shell script para configurar o GPIO dos motores DC

'

# ativar portas do GPIO
echo 16 > /sys/class/gpio/export
echo 19 > /sys/class/gpio/export
echo 20 > /sys/class/gpio/export
echo 21 > /sys/class/gpio/export

# declarar as portas como saídas
echo out > /sys/class/gpio/gpio16/direction
echo out > /sys/class/gpio/gpio19/direction
echo out > /sys/class/gpio/gpio20/direction
echo out > /sys/class/gpio/gpio21/direction
