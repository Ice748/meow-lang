#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "interpreter.h"

void println(char *arg);
void print(char *arg);
void input(char *arg);
void get_char(char *arg);
void clear(void);

int console_module(char *ptr);

#endif
