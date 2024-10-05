#include <stdarg.h>
#include <stdio.h>

#include "color_print.h"

void ColorPrint(const char color[], const char* format, ...)
{
    va_list arguments;
    printf("%s", color);

    va_start(arguments, format);
    vprintf(format, arguments);

    printf("%s", EndColor);

    va_end(arguments);
}
