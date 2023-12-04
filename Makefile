# Define the common flags and compiler
CC = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror

# Target for light_sampler
light_sampler: light_sampler.c sampler.c button.c joystick.c time.c LEDmatrix.c
	$(CC) $(CFLAGS) light_sampler.c sampler.c button.c joystick.c time.c LEDmatrix.c -o light_sampler -lpthread
	cp light_sampler ~/cmpt433/public/myApps/

# Target for noworky
noworky: noworky.c
	gcc $(CFLAGS) -Wshadow noworky.c -o noworky
	cp noworky $(HOME)/cmpt433/public/myApps/

.PHONY: all clean

all: light_sampler noworky

clean:
	rm -f light_sampler noworky
