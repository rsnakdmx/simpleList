#pragma once
#ifndef _SLINKED_H_
#define _SLINKED_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

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

//Definicion de inline
inline bool isEmpty(simpList_t * restrict gInit){ 
	return (!gInit->begin) ? true : false; 
}
inline const int32_t getSize(simpList_t * restrict gInit){ 
	return gInit->size; 
}
//Declaracion de funciones
simpList_t *createStrList();
simpList_t *createNumList();
void addStrAtEnd(simpList_t * restrict * restrict, const char * restrict);
void addStrAtBegining(simpList_t * restrict * restrict, const char * restrict);
void addStrAtPosition(simpList_t * restrict * restrict, const int32_t, 
		const char * restrict);
void addNumAtEnd(simpList_t * restrict * restrict, const float);
void addNumAtBegining(simpList_t * restrict * restrict, const float);
void addNumAtPosition(simpList_t * restrict * restrict, const int32_t, const float);
void printStr(simpList_t * restrict);
void printNum(simpList_t * restrict, const int32_t); //(Lista, numero de decimales)
void reindex(simpList_t * restrict * restrict);
node_t *searchNode(simpList_t * restrict, const int32_t);
void deleteNode(simpList_t * restrict * restrict, const int32_t);
void cleanList(simpList_t * restrict);
void destroyList(simpList_t * restrict);
void reverse(simpList_t * restrict * restrict);
void mergeSort(simpList_t * restrict * restrict);
void mergeSortNum(node_t * restrict * restrict);
void mergeSortStr(node_t * restrict * restrict);
node_t *sortedMergeNum(node_t * restrict, node_t * restrict);
node_t *sortedMergeStr(node_t * restrict, node_t * restrict);
void frontBackSplit(node_t * restrict, node_t * restrict * restrict,
    node_t * restrict * restrict);

#endif