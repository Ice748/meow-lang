#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdlib.h>
#include "interpreter.h"

extern char *variablesChar = NULL;
extern int *variablesInt = NULL;

extern size_t charCount;
extern size_t intCount;

void newChar(size_t *arg);
void newInt(size_t *arg);

int variables_module(char *ptr);

#endif
