#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "num.h"

#define MAX_array 256

typedef int ** STACK;
typedef int * STACKel;

STACK stack_init();

void stack_push(STACK S, int key);

int stack_pop(STACK S);

STACKel stack_freeNode(STACKel curr);

void stack_reverse(STACK S, STACK tmp);

void stack_print(STACK S);

void stack_random(STACK S, int n);

int stack_isEmpty(STACK S);

int stack_isFull(STACK S);


#endif