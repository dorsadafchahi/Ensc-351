all:

	arm-linux-gnueabihf-gcc -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror light_sampler.c -o light_sampler -lpthread

	cp light_sampler ~/ensc351/public/myApps/
