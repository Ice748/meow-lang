#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *getArg(char *str);
int run(FILE *file);

#endif
