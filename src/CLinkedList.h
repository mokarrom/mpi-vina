/* File      : CLinkedList.h
*  Author    : Md Mokarrom Hossain
*  Username  : x2013idf
*  Course    : CSCI 522
*  Purpose   : Linked list(C-type) declaration for storing ligands.
*/

#ifndef CLINKEDLIST_H_INCLUDED
#define CLINKEDLIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIGAND_NAME_LENGTH 25

struct ligand {
    char ligandName[MAX_LIGAND_NAME_LENGTH];
    struct ligand *next;
};

typedef struct ligand Ligand;

struct ligandList {
    Ligand *head;
};

typedef struct ligandList LigandList;

/* initialize an empty list */
void InitLigandList (LigandList *lgndList);

/* insert val at front */
void InsertFront(LigandList *lgndList, char lName[MAX_LIGAND_NAME_LENGTH]);

/* insert val at back */
void InsertBack(LigandList *lgndList, char lName[MAX_LIGAND_NAME_LENGTH]);

/* returns list length */
unsigned int length (LigandList *lgndList);

/* deletes list and clear the memory occupied by list item */
void ClearLigandList (LigandList *lgndList);

/* print the list items */
void PrintLigands(LigandList *lgndList);

#endif // CLINKEDLIST_H_INCLUDED
