#include "queue.h"

//Inizializzazione della Coda di MAX_array elementi
QUEUE queue_init() {
    QUEUE coda = NULL;
    if(coda = (int **)calloc(MAX_array+2,sizeof(int *)))    {
        if(!(coda[0] = (int *)malloc(sizeof(int))) || !(coda[MAX_array] = (int *)malloc(sizeof(int))) || !(coda[MAX_array+1] = (int *)malloc(sizeof(int))))  {
            printf("[MEM] ATTENZIONE: Problema di allocazione QUEUEel - queue_init\n");
			exit(1);
        }
        *(coda[0]) = 1;   //indice di testa
        *(coda[MAX_array]) = 1;   //indice di coda
        *(coda[MAX_array+1]) = 0;   //indice del numero di elementi
    } else  {
        printf("[MEM] ATTENZIONE: Problema di allocazione QUEUE - queue_init\n");
        exit(1);
    }
    return coda;
}


//Inserimento in Coda dell'elemento
void queue_enqueue(QUEUE coda, int key) {
    if (!queue_isFull(coda)) {
        if(coda[coda[MAX_array]] = (int *)malloc(sizeof(int)))  {
            *(coda[*(coda[MAX_array])]) = key;
            *(coda[MAX_array]) = (*(coda[MAX_array]) % (MAX_array-1)) + 1; //aggiorno l'indice dell'ultima posizione
            *(coda[MAX_array]) += 1;    //incremento il contatore del numero di elementi
        } else  {
            printf("[MEM] ATTENZIONE: Problema di allocazione QUEUEel - queue_init\n");
		    exit(1);
        }
    } else {
        printf("ATTENZIONE: la Coda è piena\n");
    }
}


//Estrazione dell'elemento dalla testa della Coda
int queue_dequeue(QUEUE coda){
    int key = 0;
    if(!queue_isEmpty(coda)) {
        key = *(coda[*(coda[0])]);   //ricavo il valore dalla testa attuale della Coda
        coda[*(coda[0])] = queue_freeNode(coda[*(coda[0])]);
        *(coda[0]) = (*(coda[0]) % (MAX_array-1)) + 1; //aggiorno l'indice della testa
        *(coda[MAX_array]) -= 1;    //decremento il contatore del numero di elementi
        if(queue_isEmpty(coda)) {   //se ho svuotato la Coda
            *(coda[0]) = 1;         //resetto il valore degli indici di testa e coda
            *(coda[MAX_array]) = 1;
        }
    } else {
        printf("ATTENZIONE: la Coda è già vuota\n");
    }
    return key;
}

//Visualizzazione dell'elemento in testa alla Coda
int queue_head(QUEUE coda)	{
	if(!queue_isEmpty(coda))	{
		return *(coda[*(coda[0])]);;
	} else {
		printf("[CODA] ATTENZIONE: la Coda è vuota - queue_head\n\n");
		return 0;
	}
}

//Liberazione efficiente della memoria allocata dinamicamente
QUEUE queue_free(QUEUE coda, int del_complete)	{   //il parametro 'del_complete' == 1 libera memoria in fase di chiusura dell'applicazione
    int idx;
    for(idx=*(coda[0]);idx<=*(coda[MAX_array]);idx++)	//ciclo dal primo all'ultimo elemento della Coda
        coda[idx] = queue_freeNode(coda[idx]);   //libero il vertice dalla Coda

    if(del_complete) {  //se sto chiudendo l'applicazione
        free(coda[0]);  //dealloco gli indici di testa e coda
	    free(coda);     //dealloco la coda
        return NULL;
    } else  //se l'utente decide di eliminare la Coda
        *(coda[0]) = 1;         //resetto il valore degli indici di testa e coda
        *(coda[MAX_array]) = 1;
        *(coda[MAX_array+1]) = 0; //resetto il numero di elementi della Coda
	return coda;
}

//Deallocazione del nodo estratto
QUEUEel queue_freeNode(QUEUEel curr)	{
	free(curr);
	return NULL;
}

//Stampa della Coda
void queue_print_recv(QUEUE coda){
    int key;
    if(!queue_isEmpty(coda)) {
        key = queue_dequeue(coda);
        printf("%d ", key);
        queue_print_recv(coda);
        queue_enqueue(coda, key);
    }
}


//Salva la coda in reverse
void queue_reverse(QUEUE coda){
    int key;
    if (!queue_isEmpty(coda)) {
        key = queue_dequeue(coda);
        queue_reverse(coda);
        queue_enqueue(coda, key);
    }
}

//Stampa la Coda
void queue_print(QUEUE coda){
    queue_print_recv(coda); //stampa ricorsiva della coda
    queue_reverse(coda); //riordina della Coda in maniera inversa
}


//Controllo della Coda piena
int queue_isEmpty(QUEUE coda){
    if(*coda[0] == *coda[MAX_array] && *coda[MAX_array+1] == 0)
        return 1;
    return 0;
}


//Controllo della Coda vuota
int queue_isFull(QUEUE coda){
    if(*coda[0] == *coda[MAX_array] && *coda[MAX_array+1] == MAX_array)
        return 1;
    return 0;
}