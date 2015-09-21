/* File      : CLinkedList.c
*  Author    : Md Mokarrom Hossain
*  Username  : x2013idf
*  Course    : CSCI 522
*  Purpose   : Linked list(C-type) implementation for storing ligands.
*/

#include "CLinkedList.h"

void InitLigandList (LigandList *lgndList)
{
    lgndList->head = NULL;
    return;
}

void InsertBack(LigandList *lgndList, char lName[MAX_LIGAND_NAME_LENGTH])
{
    Ligand *ptr, *newLigand;

    newLigand = (Ligand*) malloc (sizeof (Ligand));
    strcpy (newLigand->ligandName, lName);
    newLigand->next = NULL;

    if(lgndList->head == NULL)
    {
        lgndList->head = newLigand;
    }
    else
    {
        ptr = lgndList->head;

        while (ptr->next)
        {
            ptr = ptr->next;
        }

        ptr->next = newLigand;
    }
    return;
}

void InsertFront(LigandList *lgndList, char lName[MAX_LIGAND_NAME_LENGTH])
{
    Ligand *newLigand;

    newLigand = (Ligand*) malloc (sizeof (Ligand));
    strcpy (newLigand->ligandName, lName);

    newLigand->next = lgndList->head;
    lgndList->head = newLigand;
    return;
}

unsigned int length(LigandList *lgndList)
{
    Ligand *aLigand  = lgndList->head;
    unsigned int count = 0;

    while( aLigand != NULL)
    {
        count++;
        aLigand = aLigand->next;
    }
    return count;
}

void ClearLigandList (LigandList *lgndList)
{
    Ligand *curLigand = NULL, *tmp = NULL;
    curLigand = lgndList->head;

    while( curLigand != NULL)
    {
        tmp = curLigand->next;
        curLigand->next = NULL;
        free(curLigand);
        curLigand = tmp;
    }
    lgndList->head = NULL;
}

void PrintLigands(LigandList *lgndList)
{
    printf("=========Printing the Ligand list================\n");

    Ligand *curLigand  = lgndList->head;

    while( curLigand != NULL)
    {
        printf("Ligand = %s\n", curLigand->ligandName);
        curLigand = curLigand->next;
    }

    printf("===========End Ligand list=======================\n");
}
