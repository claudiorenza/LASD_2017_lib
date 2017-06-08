#ifndef QUEUE_FUNC_H_INCLUDED
#define QUEUE_FUNC_H_INCLUDED

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "../io/io.h"
#include "../io/random.h"
#include "queue.h"

void queue_func_main();

int queue_func_menu(int isEmpty);

void queue_func_generate(QUEUE coda);

void queue_func_insertKey(QUEUE coda);

void queue_func_extract(QUEUE coda);

void queue_func_delete(QUEUE coda);

void queue_func_print(QUEUE coda);


#endif