#include "joystick.h"

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

int getDirection(){
	// double Xval = Joystick_readX();
	// double Yval = Joystick_readY();
	return 0;
}