#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define MAX_array 256


typedef int ** QUEUE;
typedef int * QUEUEel;

QUEUE queue_init();

void queue_enqueue(QUEUE coda, int key);

int queue_dequeue(QUEUE coda);

int queue_head(QUEUE coda);

QUEUE queue_free(QUEUE coda, int del_complete);
QUEUEel queue_freeNode(QUEUEel curr);

void queue_print(QUEUE coda);
void queue_print_recv(QUEUE coda);
void queue_reverse(QUEUE coda);

int queue_isEmpty(QUEUE coda);

int queue_isFull(QUEUE coda);


#endif
