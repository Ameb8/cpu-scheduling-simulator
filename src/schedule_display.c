#include <stdio.h>

#include "../include/fmt.h"
#include "../include/process.h"

#define SEPARATOR "-----------------------------------------------"

void printTimeHeader(int time) {
    printf("\n" SEPARATOR "\n\tTime:\t%d", time);
}