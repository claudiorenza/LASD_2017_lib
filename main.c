#include <stdio.h>
#include <time.h>

#include "stack/stack_func.h"
#include "queue/queue_func.h"

int main()  {
    srand(time(NULL));		//funzione per la generazione casuale di valori
	io_clearScreen();
	printf("\t\t\tLibreria Gruppo 32 - MENU PRINCIPALE\n");
	
	int choice;
	do  {

		printf("Quale libreria vuoi utilizzare?\n\t1. Stack\t2. Coda\n\nSCELTA: ");
		if((choice = io_getInteger()) < 1 || choice > 2)
			printf("ATTENZIONE: Valore non valido\n\n");
	}while(choice < 1 || choice > 2);

	if(choice == 1)
		stack_func_main();
	else if(choice == 2)
		queue_func_main();

	return 1;
}
