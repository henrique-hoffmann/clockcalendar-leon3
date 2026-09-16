#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <stdio.h>
#include "Oled.h"

#ifndef OLED
#define OLED 1
#endif

using namespace std;

//Function that allow printing to either the OLED or the std output
void printGeneric(char str[], int line);

#endif





