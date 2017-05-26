#include "list.h"

//Inizializzazione lista
ROOTlist list_init() {
    ROOTlist lista = malloc(sizeof(struct RootListaAlbero));
    lista->L = NULL;
    lista->L_last = NULL;   //utile per fare un append a tempo costante (senza scorrere tutte i nodi)
    return lista;
}

//Nuovo nodo della lista
LIST list_newNode(int key)    {
    LIST node = (struct Lista *)malloc(sizeof(struct Lista));
    node->key = key;
    node->next = NULL;
    printf("DEBUG newNode: [%d] = %d\n", el->idx, el->elem);
    return node;
}

//Aggiunta di un nuovo nodo alla lista in testa e puntamento all'ultimo elemento
void list_insertHead(ROOTlist lista, int key) {
    if(lista->L)   {
        LIST tmp = lista->L->next;
        lista->L = list_newNode(key);
        lista->L_next = tmp;
    } else  {   //nel caso di lista vuota
        lista->L = list_newNode(key);
        lista->L_last = lista->L;
    }
}


//Aggiunta di un nuovo nodo alla lista in ultima posizione e puntamento all'ultimo elemento
void list_insertAppend(ROOTlist lista, int key) {
    if(lista->L_last)   {
        lista->L_last->next = list_newNode(key);
        lista->L_last = lista->L_last->next;
    } else  {   //nel caso di lista vuota
        lista->L = list_newNode(key);
        lista->L_last = lista->L;
    }
}

//Eliminazione elemento della lista
void list_delKey(ROOTlist lista, int key) {
    LIST L_curr = lista->L;
    LIST L_prev = NULL;
    while(L_curr && L_curr->key != key) {   //ciclo fin quando non trovo la chiave
        L_prev = L_curr;
        L_curr = L_curr->next;
    }
    if(L_curr)  {   //se è stata trovata la chiave (ovvero, il ciclo si è fermato su un nodo)
        if(L_prev)  //se si tratta di un nodo interno (ovvero, non è la testa della lista)
            L_prev->next = L_curr->next; //assegno al next del nodo precedente, il nodo successivo presente nell'elemento da cancellare
        else //se si tratta invece della testa
            lista->L = L_curr->next; //cambio la testa di tutta la lista

        if(L_curr == lista->L_last) //se l'elemento da cancellare è la coda della lista
            lista->L_last = L_prev; //gli assegno il nuovo ultimo nodo

        L_curr->next = NULL;
        free(L_curr);   //dealloco il nodo
    } else  
        printf("ATTENZIONE: elemento della lista non presente\n\n");
}

//Eliminazione elemento della lista
void list_print(ROOTlist lista) {
    while(L_curr) {   //ciclo fin quando non trovo la chiave
        printf("%d -> ", L_curr->key);
        L_curr = L_curr->next;
    }
    printf("\n");
}
