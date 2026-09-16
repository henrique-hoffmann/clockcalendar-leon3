#include "utils.h"

void printGeneric(char str[], int line){

	if (OLED) {
		//Clear the line and go to the beginning before printing
		clearLine(line);
		printString(str);
	}
	else{
		cout << str << endl;
	}
}