#include "stack.h"

//Inizializzazione dello stack di MAX_stack elementi
STACK stack_init() {
    STACK pila = (int **)calloc(MAX_stack, sizeof(int *));
	pila[0] = (int *)malloc(sizeof(int));
	*(pila[0]) = 0;
    return pila;
}


//Inserimento in testa dell'elemento nello Stack
void stack_push(STACK pila, int key){
	if(!stack_isFull(pila)){
		*(pila[0]) += 1;
		pila[*(pila[0])] = (int *)malloc(sizeof(int));
		*(pila[*(pila[0])]) = key;
	} else 
		printf("[STACK] ATTENZIONE: lo Stack è pieno - stack_push\n\n");
}


//Estrazione dell'elemento in testa allo Stack
int stack_pop(STACK pila)	{
	if(!stack_isEmpty(pila))	{
		int val = *(pila[*(pila[0])]);
		pila[*(pila[0])] = stack_freeNode(pila[*(pila[0])]);
		*(pila[0]) -= 1;
		return val;
	} else {
		printf("[STACK] ATTENZIONE: lo Stack è vuoto - stack_pop\n\n");
		return 0;
	}
}


//Liberazione efficiente della memoria allocata dinamicamente
STACK stack_free(STACK pila, int del_complete)	{   //il parametro 'del_complete' == 1 libera memoria in fase di chiusura dell'applicazione
    int idx;
    for(idx=1;idx<=*(pila[0]);idx++)	      //ciclo solo fino all'ultima riga 
        pila[idx] = stack_freeNode(pila[idx]);   //libero il vertice dallo Stack

    if(del_complete) {  //se sto chiudendo l'applicazione
        free(pila[0]);  //dealloco il numero di elementi del stack
	    free(pila);     //dealloco il stack
        return NULL;
    } else  //se l'utente decide di eliminare il stack
        *(pila[0]) = 0; //resetto il numero di elementi del stack
	return pila;
}


//Deallocazione del nodo estratto
STACKel stack_freeNode(STACKel curr)	{
	free(curr);
	return NULL;
}

//Ordinamento inverso dello Stack utile per la stampa
void stack_reverse(STACK pila, STACK tmp){
	int key;
	if(!stack_isEmpty(pila)){
		key = stack_pop(pila);
		stack_push(tmp, key);
		stack_reverse(pila, tmp);
		stack_push(pila, key);
	}
}

//Stampa dello Stack 
void stack_print(STACK pila){
	int key;
	if(!stack_isEmpty(pila)){
		key = stack_pop(pila);
		printf("%d\n", key);
		stack_print(pila);
		stack_push(pila, key);
	}
}


// Ritorna 1 se lo STACK e' vuoto, 0 altrimenti
int stack_isEmpty(STACK pila){
	if(*(pila[0]) == 0)
		return 1;
	return 0;
}


// Ritorna 1 se lo STACK e' pieno, 0 altrimenti
int stack_isFull(STACK pila){
	if(*(pila[0]) == MAX_stack)
		return 1;
	return 0;
}