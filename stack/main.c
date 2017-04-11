#include <stdio.h>
#include <time.h>

#include "stack.h"
#include "stack_func.h"

int main()  {
    srand(time(NULL));		//funzione per la generazione casuale di valori

	STACK pila = stack_init();	//inizializzazione della struttura

	int choiceMenu;
	do	{
		io_clearScreen();
		switch(choiceMenu = stack_func_menu(stack_isEmpty(pila)))	{	//chiamata del menu principale con scelta dell'albero con controllo di esistenza della pila
			case 1:
				printf("GENERAZIONE STACK\n\n");
				stack_func_generate(pila);
				break;
			case 2:
				printf("INSERIMENTO NUOVO ELEMENTO NELLO STACK\n\n");
                stack_func_insertKey(pila);
				break;
			case 3:
				printf("STAMPA STACK\n\n");
                stack_print(pila);
				break;
			case 4:
				printf("ESTRAZIONE ELEMENTO IN TESTA\n\n");
				stack_func_extract(pila);
				break;
            case 5:
				printf("CANCELLAZIONE STACK\n\n");
				stack_func_delete(pila);
				break;
            case 6:
				printf("SESSIONE TERMINATA\n\n");
		}
		io_pressKey();
	}while(choiceMenu != 6);

	pila = stack_free(pila, 1); //con il parametro '1', dealloco completamente lo stack
	return 1;
}
