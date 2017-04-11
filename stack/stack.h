#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "num.h"

#define MAX_array 256

typedef int ** STACK;
typedef int * STACKel;

STACK stack_init();

void stack_func_generate(STACK pila);

void stack_push(STACK pila, int key);

int stack_pop(STACK pila);

STACK stack_free(STACK pila, int del_complete);

STACKel stack_freeNode(STACKel curr);

void stack_reverse(STACK pila, STACK tmp);

void stack_print(STACK pila);

int stack_isEmpty(STACK pila);

int stack_isFull(STACK pila);


#endif