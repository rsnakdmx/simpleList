#pragma once
#ifndef _SLINKED_H_
#define _SLINKED_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

#define STACK_SZ 335544320
#define THREADS 2

static bool inUse;
pthread_mutex_t mtx;
pthread_t thr[THREADS];

enum types{
	string,
	real
};

typedef struct Node{ //Nodo
	void * restrict data;
	struct Node * restrict next;
	int32_t idx;
}node_t;

typedef struct List{ //Cabeza
	node_t * restrict begin; //Nodos que apuntan al final y actual respectivamente
	node_t * restrict tail;
	int32_t size;
	int32_t type;
}simpList_t;

//Pregunta del retorno de funciones: "¿Hubo error?"

//Definicion de inline
static inline bool isEmpty(simpList_t * restrict gInit){ 
	return !gInit->begin; 
}

static inline const int32_t getSize(simpList_t * restrict gInit){ 
	return gInit->size; 
}

static inline void destroyList(simpList_t * restrict gInit){
	free(gInit);
}

static inline node_t *createNode(){
	return (node_t*)calloc(0x1,sizeof(node_t));
}

//Declaracion de funciones
static simpList_t *createList(int32_t);
static void *assignData(void * restrict, int32_t);
static bool addStrAtEnd(simpList_t * restrict * restrict, const char * restrict);
static bool addStrAtBegining(simpList_t * restrict * restrict, const char * restrict);
static bool addStrAtPosition(simpList_t * restrict * restrict, const int32_t, 
		const char * restrict);
static bool addNumAtEnd(simpList_t * restrict * restrict, const float);
static bool addNumAtBegining(simpList_t * restrict * restrict, const float);
static bool addNumAtPosition(simpList_t * restrict * restrict, const int32_t, const float);
static bool printList(simpList_t * restrict, const int32_t); //(Lista, numero de decimales)
static bool reindex(simpList_t * restrict * restrict);
static node_t *searchNode(simpList_t * restrict, const int32_t);
static bool deleteNodeByIndex(simpList_t * restrict * restrict, const int32_t);
static bool deleteNodeByStr(simpList_t * restrict * restrict, const char * restrict);
static bool deleteNodeByNum(simpList_t * restrict * restrict, const float);
static void cleanList(simpList_t * restrict);
static bool reverse(simpList_t * restrict * restrict);
static bool mergeSort(simpList_t * restrict * restrict);
static void mergeSortNum(node_t * restrict * restrict);
static void mergeSortStr(node_t * restrict * restrict);
static node_t *sortedMergeNum(node_t * restrict, node_t * restrict);
static node_t *sortedMergeStr(node_t * restrict, node_t * restrict);
static node_t *splitList(node_t * restrict);

#include "simpleList.c"

#endif