SRC=$(wildcard libs/rpi_ws281x/*.c)

build: 
	g++ -std=c++17 -Wall -fpermissive -o test test.cpp libs/rpi_ws281x/ws2811.c  libs/rpi_ws281x/pcm.c libs/rpi_ws281x/dma.c libs/rpi_ws281x/mailbox.c libs/rpi_ws281x/pwm.c libs/rpi_ws281x/rpihw.c
