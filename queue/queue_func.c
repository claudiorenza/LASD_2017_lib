#include "queue_func.h"

//Funzione prinicpale delle Codde
void queue_func_main()  {
	QUEUE coda = queue_init();	//inizializzazione della struttura

	int choiceMenu;
	do	{
		io_clearScreen();
		switch(choiceMenu = queue_func_menu(queue_isEmpty(coda)))	{	//chiamata del menu principale con scelta dell'albero con controllo di esistenza della coda
			case 1:
				printf("GENERAZIONE CODA\n\n");
				queue_func_generate(coda);
				break;
			case 2:
				printf("INSERIMENTO NUOVO ELEMENTO NELLA CODA\n\n");
                queue_func_insertKey(coda);
				break;
			case 3:
				printf("STAMPA CODA\n\n");
                queue_func_print(coda);
				break;
			case 4:
				printf("ESTRAZIONE ELEMENTO IN TESTA\n\n");
				queue_func_extract(coda);
				break;
            case 5:
				printf("CANCELLAZIONE CODA\n\n");
				queue_func_delete(coda);
				break;
            case 6:
				printf("SESSIONE TERMINATA\n\n");
		}
		io_pressKey();
	}while(choiceMenu != 6);

	free(coda);
}

//Interfaccia utente
int queue_func_menu(int isEmpty)	{
	int choiceMenu;
	printf("\t\t\tCoda - MENU PRINCIPALE\n");
	printf("1. Genera Coda\n");
	printf("2. Inserisci nuovo elemento\n");
    if(!isEmpty)    {   //se la Coda esiste, mostro gli altri elementi del menu
        printf("3. Stampa Coda\n");
        printf("4. Estrai elemento in testa\n");
        printf("5. Cancella la Coda");
    }
    printf("\n");
    printf("6. Esci\n");
    printf("\n\n");
	do {
		printf("SCELTA: ");
		if(((choiceMenu = io_getInteger()) < 1 || choiceMenu > 6) || (isEmpty && (choiceMenu > 2 && choiceMenu < 6))) //nel caso l'utente inserisca una scelta del menu non presente
			printf("ATTENZIONE: Valore non valido\n\n");
	}while((choiceMenu < 1 || choiceMenu > 6) || (isEmpty && (choiceMenu > 2 && choiceMenu < 6)));
    io_clearScreen();   //pulizia dello schermo del terminale
	return choiceMenu;
}


//Inserisce valori random nella Coda
void queue_func_generate(QUEUE coda){
    int idx, n_elem;
    if(!queue_isEmpty(coda))	{	//se è già presente, chiedo al'utente quale operazione effettuare sulla Coda
        int choice;
        printf("ATTENZIONE: Coda già presente. Cosa preferisci fare?\n\t1. Generazione nuova Coda\t2. Inserimento nuovi elementi\n\n");
        do  {
            printf("SCELTA: ");
            if((choice = io_getInteger()) < 1 || choice > 2)
                printf("ATTENZIONE: Valore non valido\n\n");
        }while(choice < 1 || choice > 2);
        if(choice == 1) {
            queue_delete(coda);   //con '0' in parametro non elimino completamente la Coda ma solo tutti i puntatori al suo interno
            printf("\n");
            if(queue_isEmpty(coda))
                printf("Coda eliminata\n\n");
        }
    }
    int n_max;
    if(coda[0] != 0)    //se la coda non è vuota
        n_max = MAX_queue-(abs(coda[0] - coda[MAX_queue+1]));
    else
        n_max = MAX_queue;
    do  {
        printf("Quanti elementi vuoi inserire nella Coda? (1-%d): ", n_max);
        if((n_elem = io_getInteger()) < 1 || n_elem > n_max)
			printf("ATTENZIONE: Valore non valido\n\n");
	}while(n_elem < 1 || n_elem > n_max);

    for(idx=0;idx<n_elem;idx++)
        queue_enqueue(coda, random_num(1, MAX_queue));	//inserisce un numero casuale compreso fra 1 e MAX_queue
    printf("\n");
    queue_func_print(coda);
}

//Inserimento in input del valore nella Coda
void queue_func_insertKey(QUEUE coda)   {
    if(!queue_isFull(coda)) {
        int val;
        do  {
            printf("Quale valore vuoi inserire nella Coda?: ");
            if((val = io_getInteger()) < 1)
                printf("ATTENZIONE: Valore non valido\n\n");
        }while(val < 1);

        queue_enqueue(coda, val);
        printf("\n");
        queue_func_print(coda);
    } else
        printf("ATTENZIONE: la Coda è piena\n\n");
}

//Estrazione con conferma dell'elemento della Coda
void queue_func_extract(QUEUE coda) {
    printf("Valore in testa nella Coda: %d\n", coda[coda[0]]);
    char choice;
    do  {
        printf("Desideri estrarlo? (S/N): ");
        choice = toupper(io_getChar());
        if(choice != 'S' && choice != 'N')
            printf("ATTENZIONE: comando non riconosciuto\n\n");
    }while(choice != 'S' && choice != 'N');
    printf("\n");
    if(choice == 'S')   {
        printf("Valore estratto: %d\n\n", queue_dequeue(coda));
        if(!queue_isEmpty(coda))
            queue_func_print(coda);
        else
            printf("ATTENZIONE: Coda svuotata\n\n");
    }
}

//Eliminazione con conferma della Coda
void queue_func_delete(QUEUE coda)  {
    char choice;
    do  {
        printf("Sei sicuro di voler eliminare la Coda? (S/N): ");
        choice = toupper(io_getChar()); //se metto un carattere minuscolo, lo rende maiuscolo
        if(choice != 'S' && choice != 'N')
            printf("ATTENZIONE: scelta non valida\n\n");
    }while(choice != 'S' && choice != 'N');

    if(choice == 'S')   {
        queue_delete(coda);   //con '0' in parametro non elimino completamente la Coda ma solo tutti i puntatori al suo interno
        printf("\n");
        if(queue_isEmpty(coda))
            printf("Coda eliminata\n\n");
    }
}

//Stampa della coda
void queue_func_print(QUEUE coda)  {
    queue_print(coda);
    printf("\tTesta: %d - Coda: %d\n", coda[0], coda[MAX_queue+1]);
}