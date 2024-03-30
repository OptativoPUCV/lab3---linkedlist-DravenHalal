#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  //Se crea una lista y se reserva la memoria, se inicializan todos los datos en NULL para que se pueda llena y se devuelve la lista.
  List* lista = (List *)malloc(sizeof(List));
  lista->head = NULL;
  lista->tail = NULL;
  lista->current = NULL;
  return lista;
}

void * firstList(List * list) {
  if(list == NULL || list->current == NULL) return NULL;
  else{
    list->current = list->head;
    return list->head->data;
  }
}

void * nextList(List * list) {
  if(list == NULL || list->current == NULL) return NULL;
  else{
    list->current = list->current->next;
    if(list->current != NULL) return list->current->data;
    return NULL;
  }
}

void * lastList(List * list) {
  if(list == NULL || list->head == NULL) return NULL;
  list->current = list->head;
  while(list->current->next != NULL){
    list->current = list->current->next;
  }
  
  return list->current->data;
}

void * prevList(List * list) {
  if(list == NULL || list->current == NULL) return NULL;
  list->current = list->current->prev;
  if(list->current != NULL) return list->current->data;
  return NULL;
}

void pushFront(List * list, void * data) {
  Node * nuevoNodo = createNode(data);
  if(list->head == NULL){
    list->head = nuevoNodo;
    list->tail = nuevoNodo;
  }
  else{
    nuevoNodo->next = list->head;
    list->head->prev = nuevoNodo;
    list->head = nuevoNodo;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * nuevoNodo = createNode(data);
  nuevoNodo->next = list->current->next;
  nuevoNodo->prev = list->current;
  list->current->next = nuevoNodo;
  if(list->current == list->tail){
    list->tail = nuevoNodo;
  }
  
}

void * popFront(List * list) {
  return NULL;
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  if (list == NULL || list->current == NULL) {
    return NULL; // La lista está vacía o el current no está establecido
  }

  Node *currentNode = list->current;
  void *data = currentNode->data;

  // Manejo de punteros para conectar los nodos adyacentes al nodo actual
  if (currentNode->prev != NULL) {
    currentNode->prev->next = currentNode->next;
  } else {
    list->head = currentNode->next;
  }

  if (currentNode->next != NULL) {
    currentNode->next->prev = currentNode->prev;
  } else {
    list->tail = currentNode->prev;
  }

  // Actualizar el current al siguiente nodo
  list->current = currentNode->next;

  // Liberar la memoria del nodo eliminado
  free(currentNode);

  return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}