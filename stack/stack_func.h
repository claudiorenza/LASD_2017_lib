#ifndef STACK_FUNC_H_INCLUDED
#define STACK_FUNC_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include "../io/io.h"
#include "../io/random.h"
#include "stack.h"

#define MAX_stack 256

typedef int ** STACK;
typedef int * STACKel;

void stack_func_main();

int stack_func_menu(int isEmpty);

void stack_func_generate(STACK pila);

void stack_func_insertKey(STACK pila);

void stack_func_extract(STACK pila);

void stack_func_delete(STACK pila);

void stack_func_print(STACK pila);


#endif