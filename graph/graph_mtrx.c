#include "graph_mtrx.h"

GRAPH graph_mtrx_init(int idx_max)    {
    int idx, j;
    GRAPH grafo_mtrx = NULL;
    if((grafo_mtrx = malloc(sizeof(void *) * MAX_graph+1)))  { //preparo la matrice generica
        for(idx=0; idx<=10; idx++)
            grafo_mtrx[idx] = malloc(sizeof(void *) * MAX_graph+1);
        for(idx=0; idx<=10; idx++) {
            for(j=0; j<=10; j++)
                ((GRAPH)grafo_mtrx[idx])[j] = NULL;
        }
        if(idx_max >= 0)   {   //nel caso non debba fare una trasposizione, alloco il contatore
            ((GRAPH)grafo_mtrx[0])[0] = (int *)malloc(sizeof(int));
            *((int *)((GRAPH)grafo_mtrx[0])[0]) = idx_max;   //in grafo_mtrx[0][0] viene memorizzato l'indice del margine massimo
        }
        //IMPORTANTE: in grafo_mtrx[idx][0] e grafo_mtrx[0][j] (con idx,j > 1) saranno presenti idx riferimenti al dato generico del vertice associato (non necessita di struttura dati)
        //mentre in grafo_mtrx[idx][j] (con idx,j > 1) idx pesi di tipo float.
        //All'inserimento dei nuovi vertici, verranno allocati idx tipi di dato specifici nelle allocazioni *void
                //N.B.: Per allocare un nuovo riferimento in un punto della matrice: ((GRAPH)grafo_mtrx[idx])[j] = malloc(sizeof(typedata));
                //Per richiamare un dato dalla matrice: *((int *)((GRAPH)grafo_mtrx[idx])[j])
                //Per salvarsi il riferimento al dato: void key = ((GRAPH)grafo_mtrx[idx])[j]; int *counter = ((int *)grafo_mtrx[0])[0];
    } else
        printf("ATTENZIONE [MEM]: problema allocazione grafo_mtrx\n\n");
    return grafo_mtrx;
}


//F2: Inserimento di un nuovo vertice nella Matrice di Adiacenza
void graph_mtrx_insVertex(GRAPH grafo_mtrx, int idx, void key) {
    int j;
    if(idx == 0)    {   //se non � stato indicato manualmente l'indice del vertice, cerco il primo libero
        idx++;
        while(idx <= *((int *)((GRAPH)grafo_mtrx[0])[0]) && grafo_mtrx[idx])    //controllo se sono disponibili indici di vertici eliminati in precedenza
            idx++;
        if(idx > *((int *)((GRAPH)grafo_mtrx[0])[0]))    {
            *((int *)((GRAPH)grafo_mtrx[0])[0]) += 1; //se ho raggiunto il margine (quindi tutti gli indici precedenti a 'idx' sono stati gi� riempiti), aumento il contatore dell'ultimo indice
/*DEBUG*/   if(*((int *)((GRAPH)grafo_mtrx[0])[0]) != idx)
                printf("DEBUG: desincronizzazione dell'indice di margine\n\n"); //in tal caso, *((int *)((GRAPH)grafo_mtrx[0])[0]) dovr� essere sempre uguale a 'idx'
        }
    }
    ((GRAPH)grafo_mtrx[idx])[0] = ((GRAPH)grafo_mtrx[0])[idx] = elemento;         //inserimento dei riferimenti al dato nella riga e nella colonna di indice 0
    for(j=1;j<=*((int *)((GRAPH)grafo_mtrx[0])[0]);j++) {       //inserimento dei pesi 0 nelle righe e colonne
        ((GRAPH)grafo_mtrx[idx])[j] = (int *)malloc(sizeof(int));
        *((int *)((GRAPH)grafo_mtrx[idx])[j]) = 0;
        if(idx != j)    {   //evito che rialloco nuovamente nell'elemento diagonale della matrice
            ((GRAPH)grafo_mtrx[j])[idx] = (int *)malloc(sizeof(int));
            *((int *)((GRAPH)grafo_mtrx[j])[idx]) = 0;
        }
    }
    if(((GRAPH)grafo_mtrx[idx])[0]) {
        printf("Vertice ");
        graph_printNode(((GRAPH)grafo_mtrx[0])[idx], idx, Print);
        printf(" correttamente inserito\n");
    }
}


//F3: Inserimento di un nuovo arco con controllo dei vertici disponibili
void graph_mtrx_insArc(GRAPH grafo_mtrx, int idx_src, int idx_dst, int weight, int n_vrtx) {
    if(Print)   {
        int n_edge = 0, j;
        graph_printNode(((GRAPH)grafo_mtrx[idx_src])[0], idx_src, Print);
        printf(": ");
        for(j=1;j<=*((int *)((GRAPH)grafo_mtrx[0])[0]);j++) {
            if(((GRAPH)grafo_mtrx[idx_src])[j] && *((int *)((GRAPH)grafo_mtrx[idx_src])[j]) != 0)  {
                graph_printNode(((GRAPH)grafo_mtrx[0])[j], j, Print);    //stampo l'indice e il dato generico associato
                printf(" [%d] -> ", *((int *)((GRAPH)grafo_mtrx[idx_src])[j]));  //e il peso dell'arco //IMPORTANTE: rendere float
                n_edge++;
            }
        }
        printf("\n\n");
        if(n_edge < n_vrtx)   {
            printf("Vertici disponibili per ");
            graph_printNode(((GRAPH)grafo_mtrx[idx_src])[0], idx_src, Print);
            printf(":\n");
            for(j=1;j<=*((int *)((GRAPH)grafo_mtrx[0])[0]);j++) {
                if(((GRAPH)grafo_mtrx[idx_src])[j] && *((int *)((GRAPH)grafo_mtrx[idx_src])[j]) == 0 && idx_src != j)   {
                    graph_printNode(((GRAPH)grafo_mtrx[0])[j], j, Print);    //stampo l'indice e il dato generico associato
                    printf("\n");
                }
            }
            do  {
                printf("A quale indice vuoi collegare il vertice %d? ", idx_src);    //attualmente in uso come DEBUG per controllare se l'indice del vettore coincide con l'indice del dato interno
                idx_dst = io_getInteger();
                if(!((GRAPH)grafo_mtrx[0])[idx_dst])
                    printf("ATTENZIONE: vertice scelto non presente nel Grafo\n\n");
                else if(*((int *)((GRAPH)grafo_mtrx[idx_src])[idx_dst]) != 0)
                    printf("ATTENZIONE: arco gi(�) presente per la destinazione scelta\n\n");
            }while(!((GRAPH)grafo_mtrx[0])[idx_dst] || *((int *)((GRAPH)grafo_mtrx[idx_src])[idx_dst]) != 0);
            do  {
                printf("Quale peso vuoi inserire all'arco? (Numero reale): ");
                weight = io_getInteger();
                if(!weight)
                    printf("ATTENZIONE: valore non valido\n\n");
            }while(!weight);
        } else  {
            printf("ATTENZIONE: tutti gli archi uscenti sono gi� collegati con tutti gli altri vertici\n\n");
            return;
        }
    }
    *((int *)((GRAPH)grafo_mtrx[idx_src])[idx_dst]) = weight;
    printf("Arco inserito in Matrice fra idx vertici %d -> %d di peso [%d]\n", idx_src, idx_dst, *((int *)((GRAPH)grafo_mtrx[idx_src])[idx_dst]));
}


//F5: Visualizzazione del percorso minimo fra due vertici (BFS)
void graph_mtrx_path(GRAPH grafo_mtrx, int i_src, int j_dst)  {
    if(i_src != j_dst)  {
        int *pred = graph_mtrx_BFS(grafo_mtrx, i_src);
        graph_mtrx_path_print(grafo_mtrx, i_src, j_dst, pred, Print);
    } else
        printf("ATTENZIONE: Sorgente e destinazione coincidono\n\n");
}

//Visita in ampiezza con creazione e ritorno dell'array degli indici dei predecessori
int *graph_mtrx_BFS(GRAPH grafo_mtrx, int i_src)  {
    int idx, j, i_max = *((int *)((GRAPH)grafo_mtrx[0])[0]);
    int *pred = (int *)malloc(sizeof(int) * i_max);    //per futura utitlit�, dispongo anche l'array degli indici dei predecessori

    char *color = (char *)malloc(sizeof(char) * i_max);   //creo l'array dei colori associati ai vertici, quantificati in grafo_mtrx[0][0]

    QUEUE coda = queue_init(i_max);  //creo una coda che ha una grandezza massima del numero dei vertici del Grafo

    for(idx=1;idx<=i_max;idx++)    {       //inizializzazione array dei colori e dei predecessori a partire dal vertice minimo
        if(((GRAPH)grafo_mtrx[idx])[0] && idx != i_src)
            color[idx] = 'w';
            pred[idx] = -1;
    }

    color[i_src] = 'g'; //GRIGIO sul vertice sorgente
    pred[i_src]= -1;  //che non ha predecessori
    queue_enqueue(coda, i_src);
    while(!queue_check_empty(coda))    {    //ciclo fin quando non svuoto la coda
        idx = queue_dequeue(coda);    //estraggo la testa della Coda
        for(j=1;j<=i_max;j++)    {       //controllo gli adiacenti
            if(((GRAPH)grafo_mtrx[idx])[j] && *((int *)((GRAPH)grafo_mtrx[idx])[j]) != 0)    {    //se esiste l'adiacente
                if(color[j] == 'w') {  //se BIANCO
                    color[j] = 'g';
                    pred[j] = idx;
                    queue_enqueue(coda, j);
                }
            }
        }
        color[idx] = 'b';  //completo la visita del nodo in NERO
    }
    free(color);
    free(coda);
    return pred;
}

//Stampa del percorso minimo fra due vertici definito dall'array dei predecessori
void graph_mtrx_path_print(GRAPH grafo_mtrx, int i_src, int j, int *pred)  {
    if(i_src == j)
        graph_printNode(((GRAPH)grafo_mtrx[i_src])[0], i_src, Print);
    else if(pred[j] == -1)
        printf("ATTENZIONE: non esiste alcun cammino tra la sorgente e la destinazione scelta \n\n");
    else
        graph_mtrx_path_print(grafo_mtrx, i_src, pred[j], pred, Print);
        graph_printNode(((GRAPH)grafo_mtrx[j])[0], j, Print);
}



//F6: Eliminazione della Matrice di Adiacenza
GRAPH graph_mtrx_deleteGraph(GRAPH grafo_mtrx) {
    int idx, j, idx_max = *((int *)((GRAPH)grafo_mtrx[0])[0]);
    for(idx=0;idx<=idx_max;idx++)    {
        for(j=0;j<=idx_max;j++)    {
            //printf("DEBUG: %d %d\n", idx, j);
            if(((GRAPH)grafo_mtrx[idx])[j])   //se esiste un dato
                free(((GRAPH)grafo_mtrx[idx])[j]);
        }
        free(grafo_mtrx[idx]);    //dealloco la riga
        //printf("DEBUG: fine riga\n");
    }
    //printf("DEBUG: fine\n");
    return NULL;
}


//F7: Eliminazione del vertice con idx relativi archi; ritorna il numero di vertici aggiornato
int graph_mtrx_delVertex(GRAPH grafo_mtrx, int idx_del, int n_vrtx)  {
    int idx;
    for(idx=0;idx<=*((int *)((GRAPH)grafo_mtrx[0])[0]);idx++) {   //elimino idx pesi dalle righe e colonne riferite
        free(((GRAPH)grafo_mtrx[idx])[idx_del]);
        ((GRAPH)grafo_mtrx[idx])[idx_del] = NULL;
        if(idx != idx_del)    {   //se non mi trovo nella diagonale della matric
            free(((GRAPH)grafo_mtrx[idx_del])[idx]);
            ((GRAPH)grafo_mtrx[idx_del])[idx] = NULL;
        }
    }
    if(idx_del == *((int *)((GRAPH)grafo_mtrx[0])[0])) //se ho eliminato l'ultimo elemento,
        *((int *)((GRAPH)grafo_mtrx[0])[0]) -= 1;   //aggiorno anche il valore del margine massimo dell'array
    return n_vrtx-1;
}

//F8: Eliminazione dell'arco con controllo dei vertici adiacenti
void graph_mtrx_delArc(GRAPH grafo_mtrx, int idx_src) {
    int n_edge = 0, j;
    graph_printNode(((GRAPH)grafo_mtrx[idx_src])[0], idx_src, Print);
    printf(": ");
    for(j=1;j<=*((int *)((GRAPH)grafo_mtrx[0])[0]);j++) {
        if(((GRAPH)grafo_mtrx[idx_src])[j] && *((int *)((GRAPH)grafo_mtrx[idx_src])[j]) != 0)  {
            graph_printNode(((GRAPH)grafo_mtrx[0])[j], j, Print);    //stampo l'indice e il dato generico associato
            printf(" [%d] -> ", *((int *)((GRAPH)grafo_mtrx[idx_src])[j]));  //e il peso dell'arco IMPORTANTE: rendere float
            n_edge++;
        }
    }
    printf("\n\n");
    if(n_edge > 0)  {
        int idx_del;
        do  {
            printf("Quale indice dell'arco uscente vuoi eliminare dal vertice %d? ", idx_src);
            idx_del = io_getInteger();
            if(*((int *)((GRAPH)grafo_mtrx[idx_src])[idx_del]) == 0)
                printf("ATTENZIONE: arco NON presente per la destinazione scelta\n\n");
        }while(*((int *)((GRAPH)grafo_mtrx[idx_src])[idx_del]) == 0);
        *((int *)((GRAPH)grafo_mtrx[idx_src])[idx_del]) = 0;
    } else
        printf("ATTENZIONE: il vertice scelto non ha archi uscenti\n\n");
}

//F9: Conversione della struttura dati del Grafo da Matrice a Lista di Adiacenza
GRAPH graph_mtrx_convert(GRAPH grafo_mtrx)  {
    GRAPH grafo_list = graph_list_init(-1); //con il parametro '-1' non alloco un nuovo contatore, siccome lo prendo da grafo_mtrx
    int idx, j;
    //CHECK: allocazione array e liste

    grafo_list[0] = ((GRAPH)grafo_mtrx[0])[0];

    for(idx=1;idx<=*((int *)grafo_list[0]);idx++)    {
        if(((GRAPH)grafo_mtrx[idx])[0])
            graph_list_insVertex(grafo_list, idx, ((GRAPH)grafo_mtrx[idx])[0], Print);  //alloco idx vertici disponibili della lista
    }
    printf("\n");
    for(idx=1;idx<=*((int *)grafo_list[0]);idx++)    {
        if(((GRAPH)grafo_mtrx[idx])[0])   {
            for(j=1;j<=*((int *)grafo_list[0]);j++)    {       //controllo gli adiacenti
                if(((GRAPH)grafo_mtrx[idx])[j] && *((int *)((GRAPH)grafo_mtrx[idx])[j]) != 0)    {    //se esiste l'adiacente
                    graph_list_insArc(grafo_list, idx, j, *((int *)((GRAPH)grafo_mtrx[idx])[j]), NULL, -1);
                } else if(((GRAPH)grafo_mtrx[idx])[j])   //peso == 0
                    free(((GRAPH)grafo_mtrx[idx])[j]);  //dealloco l'elemento
                ((GRAPH)grafo_mtrx[idx])[j] = NULL;    //tolgo il riferimento al dato del peso, per evitare la perdita del dato nella deallocazione
            }
            ((GRAPH)grafo_mtrx[idx])[0] = ((GRAPH)grafo_mtrx[0])[idx] = NULL;     //tolgo il riferimento al dato generico, per evitare la perdita del dato nella deallocazione
        }
        free(grafo_mtrx[idx]);    //deallocazione riga
    }
    free(grafo_mtrx);   //deallocazione della Matrice
    return grafo_list;
}


//F10: Trasposizione del Grafo
void graph_mtrx_transpose(GRAPH grafo_mtrx)  {
    int tmp, idx, j;
    for(idx=1; idx<=*((int *)((GRAPH)grafo_mtrx[0])[0]); idx++)   {
        for(j=idx+1; j<=*((int *)((GRAPH)grafo_mtrx[0])[0]); j++)   { //si fa lo swap del triangolo superiore con gli elementi del triangolo inferiore
            if(((GRAPH)grafo_mtrx[idx])[j])    {
                tmp = *((int *)((GRAPH)grafo_mtrx[idx])[j]); //CHECK
                *((int *)((GRAPH)grafo_mtrx[idx])[j]) = *((int *)((GRAPH)grafo_mtrx[j])[idx]);
                *((int *)((GRAPH)grafo_mtrx[j])[idx]) = tmp;
            }
        }
    }
}

//F11: Ricerca nel grafo di un arco di ritorno, ovvero di un ciclo
void graph_mtrx_check_cycle(GRAPH grafo_mtrx)  {
    int idx=1;
    while(!((GRAPH)grafo_mtrx[idx])[0])   //vedo l'indice minimo del primo elemento presente attualmente nel grafo
        idx++;
    if(graph_mtrx_DFS(grafo_mtrx, idx))  //se c'� un ciclo, lo notifico
        printf("Il grafo contiene un ciclo\n\n");
    else
        printf("Il grafo NON contiene un ciclo\n\n");
}


//Visita in profondit� con verifica di ciclicit�
int graph_mtrx_DFS(GRAPH grafo_mtrx, int i_src)  {
    int idx, j, check_cycle = 0, i_max = *((int *)((GRAPH)grafo_mtrx[0])[0]); //intero che controlla l'effettiva presenza di un ciclo
    int *pred = (int *)malloc(sizeof(int) * i_max);    //per futura utitlit�, dispongo anche l'array degli indici dei predecessori

    char *color = (char *)malloc(sizeof(char) * i_max);   //creo l'array dei colori associati ai vertici, quantificati in grafo_mtrx[0][0]

    for(idx=i_src;idx<=i_max;idx++)    {       //inizializzazione array dei colori e dei predecessori a partire dal vertice minimo
        if(((GRAPH)grafo_mtrx[idx])[0])
            color[idx] = 'w';
            pred[idx] = -1;
    }

    for(idx=i_src;idx<=i_max;idx++)    {       //parto con la visita dei nodi a partire dal vertice minimo
        for(j=1;j<=i_max;j++)    {       //controllo gli adiacenti
            if(((GRAPH)grafo_mtrx[idx])[j] && *((int *)((GRAPH)grafo_mtrx[idx])[j]) != 0)    {    //se esiste l'adiacente
                if(color[j] == 'w')   //se BIANCO
                    check_cycle = graph_mtrx_DFS_visit(grafo_mtrx, j, pred, color, check_cycle); //visito l'elemento della lista di adiacenza
            }
        }
    }
    free(color);
    return check_cycle;
}

//Durante la visita in profondit�, posso notificare la presenza di un ciclo all'interno del grafo
int graph_mtrx_DFS_visit(GRAPH grafo_mtrx, int idx_curr, int *pred, char *color, int check_cycle)    {
    color[idx_curr] = 'g'; //GRIGIO sul vertice attuale
    int j;
    for(j=1;j<=*((int *)((GRAPH)grafo_mtrx[0])[0]);j++) {
        if(((GRAPH)grafo_mtrx[idx_curr])[j] && *((int *)((GRAPH)grafo_mtrx[idx_curr])[j]) != 0) {
            if(color[j] == 'w') {
                pred[j] = idx_curr;
                check_cycle = graph_mtrx_DFS_visit(grafo_mtrx, j, pred, color, check_cycle);
            } else if(!check_cycle && color[j] == 'g')
                check_cycle = 1;
        }
    }
    color[idx_curr] = 'b';  //completo la visita del nodo in NERO
    return check_cycle;
}

//F4: Stampa del grafo di Matrice di Adiacenza
void graph_mtrx_print(GRAPH grafo_mtrx, int showlist)   {
    int idx, j;
    for(idx=1;idx<=*((int *)((GRAPH)grafo_mtrx[0])[0]);idx++) {
        if(((GRAPH)grafo_mtrx[idx])[0])   {
            graph_printNode(((GRAPH)grafo_mtrx[idx])[0], idx, Print);
            if(showlist)  {  //si pu� richiedere dal parametro 'showlist' di mostrare la Lista di Adiacenza del vertice in esame
                printf(":");
                for(j=1;j<=*((int *)((GRAPH)grafo_mtrx[0])[0]);j++) {
                    if(((GRAPH)grafo_mtrx[idx])[j] && *((int *)((GRAPH)grafo_mtrx[idx])[j]) != 0) {
                        printf("-> ");
                        graph_printNode(((GRAPH)grafo_mtrx[j])[0], j, Print);   //stampa dell'elemento
                        printf(" [%d] ", *((int *)((GRAPH)grafo_mtrx[idx])[j])); //IMPORTANTE: rendere float
                    }
                }
            }
            printf("\n");
        }
    }
}
