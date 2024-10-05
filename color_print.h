#ifndef COLOR_PRINT_H
#define COLOR_PRINT_H

const char YellowColor[] = "\033[3;33m";
const char GreenColor[]  = "\033[3;32m";
const char RedColor[]    = "\033[3;31m";
const char EndColor[]    = "\033[0m";

void ColorPrint(const char color[], const char* format, ...);

#endif // COLOR_PRINT_H