#include "treeABR.h"

//Inserimento del nodo nell'albero
TREE treeABR_insertKey(TREE T, int key)	{
	if(T)	{
		if(key <= (*T)->elem)	//confronto dei valori con il tipo di dato dell'albero
			treeABR_insertKey((*T)->sx, key);
		else if(key > (*T)->elem);
			treeABR_insertKey((*T)->dx, key);
	} else	
		(*T) = treeABR_creaNodo(key);
	return T;
}

//Eliminazione ricorsiva dei nodi in postOrder
TREE treeABR_delete(TREE T)	{
	if(T)	{
		T->sx = treeABR_delete(T->sx);
		T->dx = treeABR_delete(T->dx);
		treeABR_nodeFree(T);
	}
	return NULL;
}

//Eliminazione del nodo
TREE treeABR_deleteKey(TREE T, int key)	{
	if(T)	{
		if (key < T->elem)	//confronto dei valori con il tipo di dato dell'albero
			T->sx = treeABR_deleteKey(T->sx, key);
		else if (key > T->elem)
			T->dx = treeABR_deleteKey(T->dx, key);
		else	{	//key trovato: Compare(key, T->elem) = 0
			TREE tmp = T;
			if(tmp->sx == NULL)	//Caso I e II: zero o un figlio
				T = tmp->dx; //aggancio al figlio destro (che può essere anche NULL)
			else if(tmp->dx == NULL)
				T = tmp->sx; //aggancio al figlio sinistro
			else	{				//Caso III: due figli
				tmp = treeABR_staccaMin(T->dx, T);		//ricerca del valore minimo
                int elem_canc = T->elem;  //key temporaneo per la sostituzione col nodo da cancellare
                T->elem = tmp->elem;	//swap col valore minimo, per la corretta deallocazione dell'key e del nodo
                tmp->elem = elem_canc;
			}
			treeABR_nodeFree(tmp); //funzione di deallocazione completa del nodo isolato (key interno e nodo in sè)
		}
	} else {
		printf("Il valore inserito non è presente nell'albero\n\n");
	}
	return T;
}

//Ricerca del valore più piccolo nei sottoalberi sinistri
TREE treeABR_staccaMin(TREE T, TREE P)	{
	if(T)	{
		if(T->sx)
			return treeABR_staccaMin(T->sx, T);	//ricerca ricorsiva del valore minimo
		else	{				//arrivato al nodo minimo
			if(T == P->sx)		//aggancio il padre al figlio del nodo da sostituire per la successiva eliminazione
				P->sx = T->dx;
			else
				P->dx = T->dx;
		}
	}
	return T;
}


//Visita in ordine di un albero con contatore del numero dei nodi
int treeABR_inOrder(TREE T, int i, FN_IO Print)	{
	if(T)	{
		i = treeABR_inOrder(T->sx, i, Print);
		i = treeABR_visita(T, i, Print);
		i = treeABR_inOrder(T->dx, i, Print);
	}
	return i;
}
