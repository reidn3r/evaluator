#ifndef LIST_H
#define LIST_H

#include "nodes.h"
#include <stdbool.h>

// essa função será usada tanto para a stack quanto para a fila
bool isEmpty(node* node); 

// funções para a fila
void listAppend(char* elem, node** list);
void listEmpty(node** list);
void listPrint(node* list);
void listCopy(char** dest, char* elem);
char* listPop(node** list);
char* lastElem(node* list);

#endif