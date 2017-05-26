#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct CodaPrAlbero * PRQUEUEnode;


struct Lista   {
    int key;
    struct Lista *next;
};
typedef struct Lista * LIST;

struct RootLista  {
    LIST L;
    LIST L_last;    //puntatore all'ultimo elemento della lista
};
typedef struct RootListaAlbero * ROOTlist;


ROOTlist list_init();

LIST list_newNode(int key);

void list_insertHead(ROOTlist lista, int key);

void list_insertAppend(ROOTlist lista, int key);

void list_visit(ROOTlist lista, PRQUEUEnode top);


#endif // LIST_H_INCLUDED
