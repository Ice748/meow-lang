#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "modules/console.h"

char *getArg(char *str);
int run(FILE *file);

#endif
