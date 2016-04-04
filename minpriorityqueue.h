#ifndef MINPRIORITYQ_H
#define MINPRIORITYQ_H

#include <stdbool.h>

// https://en.wikipedia.org/wiki/Priority_queue
// la file de priorité est implémentée à l'aide d'un tas binaire (Binary Heap)
// https://en.wikipedia.org/wiki/Binary_heap

typedef struct {
    int *data;
    float *prio;
    int *index;
    int len;
	int size;
} heap_t;

// crée une file de priorité de n éléments maximum
// elle sera à initialiser avec n égal au nombre de sommets du graphe
heap_t *create_heap(int n);

// ajoute dans la file de priorité la donnée data avec la priorité priority
// lorsqu'on ajoutera un sommet du graphe on y mettra :
// data = identifiant du sommet
// priority = distance à parcourir pour atteindre le sommet
void push_heap(heap_t *h, int data, float priority);

// extrait de la file de priorité la donnée data la plus prioritaire
// lorsqu'on fera appel à cet fonction, elle nous retounera l'identifiant
// du sommet dont la distance est la plus petite
int extract_min(heap_t *h);

//retourne vrai si la file est vide
bool isEmpty(heap_t *h);

//retourne la priorité de v
// si v n'existe pas alors get_priority renvoi -1.0
float get_priority(heap_t *h, int v);

//retourne vrai si v est dans h
bool is_in(heap_t *h, int v);

#endif //MINPRIORITYQ_H