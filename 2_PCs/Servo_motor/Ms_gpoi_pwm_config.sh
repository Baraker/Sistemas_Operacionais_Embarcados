#!/bin/bash

echo 20000000 > /sys/class/pwm/pwmchip0/pwm0/period
echo 20000000 > /sys/class/pwm/pwmchip0/pwm1/period

echo 1500000 > /sys/class/pwm/pwmchip0/pwm0/duty_cycle
echo 1500000 > /sys/class/pwm/pwmchip0/pwm1/duty_cycle

echo 1 > /sys/class/pwm/pwmchip0/pwm0/enable
echo 1 > /sys/class/pwm/pwmchip0/pwm1/enable
