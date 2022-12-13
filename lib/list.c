#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include "enemy.h"
#include "list.h"

void ListLSECreate(ListLSE *list)
{
    list->init = NULL;
    list->end = NULL;
}

bool ListLSEIsEmpty(ListLSE list)
{
    return list.init == NULL && list.end == NULL;
}

bool ListLSEInsertEnd(ListLSE *list, Enemy enemy)
{
    struct Node *aux;

    aux = (struct Node *)malloc(sizeof(struct Node));

    if (aux == NULL)
        return false;

    aux->enemy = enemy;

    if (ListLSEIsEmpty(*list))
    {
        list->init = aux;
        list->end = aux;

        aux->next = NULL;

        return true;
    }

    list->end->next = aux;
    aux->next = NULL;
    list->end = aux;

    return true;
}

int ListLSECountElements(ListLSE list)
{
    int counter = 0;
    struct Node *aux;

    if (ListLSEIsEmpty(list))
        return 0;

    aux = list.init;

    while (aux != NULL)
    {
        counter += 1;
        aux = aux->next;
    }

    return counter;
}

int ListLSERemove(ListLSE *list, Enemy enemy)
{
    struct Node *aux, *before, *current;

    if (ListLSEIsEmpty(*list))
        return -1;

    // Remove first element of a unitary list
    if (list->init == list->end && list->init != NULL && list->init->enemy.id == enemy.id)
    {
        aux = list->init;

        list->init = NULL;
        list->end = NULL;

        free(aux);

        return 1;
    }

    // Remove first element of a non unitary list
    if (list->init != list->end && list->init->enemy.id == enemy.id)
    {
        aux = list->init;

        list->init = list->init->next;

        free(aux);

        return 1;
    }

    // Remove from any other position at of the list
    before = list->init;
    current = before->next;

    while (current->enemy.id != enemy.id && current->next != NULL)
    {
        before = current;
        current = current->next;
    }

    if (current == NULL)
    {
        return -1;
    }

    // Got to the last element at the list
    else if (current->next == NULL)
    {
        aux = current;

        before->next = NULL;
        list->end = before;

        free(aux);

        return 1;
    }

    else
    {
        aux = current;

        before->next = current->next;

        free(aux);

        return 1;
    }
}

Enemy *ListLSEInit(ListLSE list)
{
    if (!ListLSEIsEmpty(list))
        return &(list.init->enemy);

    exit(1);
}