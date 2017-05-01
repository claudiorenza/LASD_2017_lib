#ifndef TREEABR_H_INCLUDED
#define TREEABR_H_INCLUDED


typedef struct Albero * TREE;

TREE treeABR_insertKey(TREE T, int key);

TREE treeABR_delete(TREE T);

TREE treeABR_deleteKey(TREE T, int key);

TREE treeABR_staccaMin(TREE T, TREE P);

int treeABR_inOrder(TREE T, int i);

#endif