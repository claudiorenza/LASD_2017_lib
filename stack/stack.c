#include "stack.h"

//Inizializzazione dello stack di MAX_array elementi
STACK stack_init() {
    STACK S = (int **)calloc(MAX_array, sizeof(int *));
	S[0] = (int *)malloc(sizeof(int));
	*(S[0]) = 0;
    return S;
}


//Inserimento in testa dell'elemento nello Stack
void stack_push(STACK S, int key){
	if(!stack_isFull(S)){
		*(S[0])++;
		S[*(S[0])] = (int *)malloc(sizeof(int));
		*(S[*(S[0])]) = key;
	} else 
		printf("ATTENZIONE: lo stack è pieno\n\n");
}


//Estrazione dell'elemento in testa allo Stack
int stack_pop(STACK S)	{
	if(!stack_isEmpty(S))	{
		int val = *(S[*(S[0])]);
		S[*(S[0])] = stack_freeNode(S[*(S[0])]);
		*(S[0])--;
		return val;
	} else {
		printf("ATTENZIONE: lo stack è vuoto\n\n");
		return 0;
	}
}

//Deallocazione del nodo estratto
STACKel stack_freeNode(STACKel curr)	{
	free(curr);
	return NULL
}

//Ordinamento inverso dello Stack utile per la stampa
void stack_reverse(STACK S, STACK tmp){
	int key;
	if(!stack_isEmpty(S)){
		key = stack_pop(S);
		stack_push(tmp, key);
		stack_reverse(S, tmp);
		stack_push(S, key);
	}
}

//Stampa dello Stack 
void stack_print(STACK S){
	int key;
	if(!stack_isEmpty(S)){
		key = stack_pop(S);
		printf(" %d", key);
		print_stack(S);
		stack_push(S, key);
	}
}

//Generazione di uno Stack con valori randomici
void stack_random(STACK S, int n) {
    int idx;
    for(idx=0;idx<n;idx++) {
        stack_push(S, random_num(int a, int b));
    }
}


// Ritorna 1 se lo STACK e' vuoto, 0 altrimenti
int stack_isEmpty(STACK S){
	if(*(S[0]) == 0)
		return 1;
	return 0;
}


// Ritorna 1 se lo STACK e' pieno, 0 altrimenti
int stack_isFull(STACK S){
	if(*(S[0]) == MAX_array)
		return 1;
	return 0;
}