DC_motor_ctrl: DC_gpio.o gpio_dev_mem.o
	gcc $(CFLAGS) -o DC_motor_ctrl DC_gpio.o gpio_dev_mem.o
DC_gpio.o: DC_gpio.c gpio_dev_mem.h
	gcc $(CFLAGS) -c DC_gpio.c
gpio_dev_mem.o: gpio_dev_mem.c gpio_dev_mem.h
	gcc $(CFLAGS) -c gpio_dev_mem.c
clean:
	rm -f *.o DC_motor_ctrl