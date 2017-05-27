#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct CodaPrAlbero * PRQUEUEnode;


struct Lista   {
    int weight;
    int salita;
    struct Lista *next;
};
typedef struct Lista * LIST;


LIST list_newNode(int weight, int salita);

void list_insertHead(LIST lista, int key);

void list_delKey(LIST lista, int key);


#endif // LIST_H_INCLUDED
