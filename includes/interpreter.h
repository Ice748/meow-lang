#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "meow-lang.h"
#include "modules/console.h"

char *getArgString(char *ptr, const char *module, const char *function);
int *getArgVoid(char *ptr, const char *module, const char *function);

int run(const char *file_name);

#endif
