#ifndef TREEABR_H_INCLUDED
#define TREEABR_H_INCLUDED

struct Albero   {
    int elem;
    struct Albero **sx;
    struct Albero **dx;
}

typedef struct Albero ** TREE;
typedef struct Albero * TREEel;

TREE treeABR_insertKey(TREE T, int key);

TREE treeABR_delete(TREE T);

TREE treeABR_deleteKey(TREE T, int key);

TREE treeABR_staccaMin(TREE T, TREE P);

int treeABR_inOrder(TREE T, int i);

#endif