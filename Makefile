tempmake: src/uart_modbus/uart_modbus.c src/crc16/crc16.c src/sensorBME280/bme280.c src/csv/csv.c src/driver_lcd_16x2/lcd.c src/PID/pid.c src/on_off/on_off.c src/gpio/gpio.c src/menu/menu.c
	gcc src/main.c  src/uart_modbus/uart_modbus.c src/crc16/crc16.c src/sensorBME280/bme280.c src/csv/csv.c src/driver_lcd_16x2/lcd.c src/PID/pid.c src/on_off/on_off.c src/gpio/gpio.c src/menu/menu.c -lwiringPi -o control

run: 
	./control
