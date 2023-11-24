#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define JoyX "/sys/bus/iio/devices/iio:device0/in_voltage2_raw"
#define JoyY "/sys/bus/iio/devices/iio:device0/in_voltage3_raw"

double Joystick_readX() {
	FILE *voltage_file = fopen(JoyX, "r");
	if (!voltage_file) {
		printf("ERROR: Unable to open voltage input file\n");
		exit(-1);
	}
	int value = 0;
	fscanf(voltage_file, "%d", &value);
	fclose(voltage_file);
    double val = value;
	return val;
}

double Joystick_readY() {
	FILE *voltage_file = fopen(JoyY, "r");
	if (!voltage_file) {
		printf("ERROR: Unable to open voltage input file\n");
		exit(-1);
	}
	int value = 0;
	fscanf(voltage_file, "%d", &value);
	fclose(voltage_file);
    double val = value;
	return val;
}