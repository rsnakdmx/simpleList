#include "simpleList.h"
/*sigsegv agota la memoria disponible para el stack, revisar la forma de 
  evitar que el stack se desborde.

Compilacion con: 
gcc -Wall -std=c11 -O3 -march=native -fstack-protector-all -o lista.exe
 shareUtil.c simpleList.c firstUseList.c -Wl,--stack,335544320

* Se marcan hasta 320MB (bytes en el comando) de stack disponibles para la ejecucion
*/

/*
Con qsort se muestra muy rapido el ordenamiento y el gasto de memoria no es tan 
grande, pareciera ser una buena opcion
*/

//Definicion en la unidad de traduccion, se indica extern
extern bool isEmpty(simpList_t * restrict);
extern const int32_t getSize(simpList_t * restrict);

//Definicion de funciones
simpList_t *createStrList(){
	simpList_t *newList = (simpList_t*)calloc(1,sizeof(simpList_t));
	newList->type = string;
	return newList; 
}

simpList_t *createNumList(){
	simpList_t *newList = (simpList_t*)calloc(1,sizeof(simpList_t));
	newList->type = real;
	return newList;
}

void addStrAtEnd(simpList_t * restrict * restrict head, 
	const char * restrict data){
	if ((*head)->type == real) {
		printf("\nError: Incorrect type of list\n");
		return; 
	
	} else {
		node_t *newNode = (node_t*)calloc(1,sizeof(node_t));
		++(*head)->size;

		if (!(*head)->begin) {
			(*head)->tail = newNode;
			(*head)->tail->idx = (*head)->size;
			(*head)->tail->data = 
				(char*)calloc(strlen(data)+1,sizeof(char));
			strcpy((*head)->tail->data,data);
			(*head)->begin = (*head)->tail;
	
		} else {
			(*head)->tail->next = newNode;
			(*head)->tail->next->idx = (*head)->size;
			(*head)->tail->next->data = 
				(char*)calloc(strlen(data)+1,sizeof(char));
			strcpy((*head)->tail->next->data,data);
			(*head)->tail = (*head)->tail->next;
		}
	}
}

void addStrAtBegining(simpList_t * restrict * restrict head, 
	const char * restrict data){
	if ((*head)->type == real) {
		printf("\nError: Incorrect type of list\n");
		return;
	
	} else {
		node_t * restrict newNode = (node_t*)calloc(1,sizeof(node_t)), 
			* restrict aux = NULL;
		++(*head)->size;

		if (!(*head)->begin) {
			(*head)->begin = newNode;
			(*head)->begin->idx = (*head)->size;
			(*head)->begin->data = (char*)calloc(strlen(data)+1,sizeof(char));
			strcpy((*head)->begin->data,data);
			(*head)->tail = (*head)->begin;

		} else { 	
			aux = (*head)->begin;
			(*head)->begin = newNode;
			(*head)->begin->idx = (*head)->size;
			(*head)->begin->data = (char*)calloc(strlen(data)+1,sizeof(char));
			strcpy((*head)->begin->data,data);
			(*head)->begin->next = aux;
		}
	}
}

void addStrAtPosition(simpList_t * restrict * restrict head, 
	const int32_t idx, const char * restrict data){
	if ((*head)->type == real) {
		printf("\nError: Incorrect type of list\n");
		return;
	
	} else {
		bool exist = false;
		node_t * restrict aux = NULL, * restrict tmp = (*head)->begin;

		if (!(*head)->begin)
			return;
	
		else {
			while ((*head)->begin->idx != idx && (*head)->begin)
				(*head)->begin = (*head)->begin->next;

			if ((*head)->begin)
				exist = true;

			if (exist) {
				++(*head)->size;
				aux = (*head)->begin->next;
				(*head)->begin->next = (node_t*)calloc(1,sizeof(node_t));
				(*head)->begin->next->data = 
					(char*)calloc(strlen(data)+1,sizeof(char));
				strcpy((*head)->begin->next->data,data);
				(*head)->begin->next->idx = (*head)->size;
				(*head)->begin->next->next = aux;
				(*head)->begin = tmp;

				if ((*head)->begin->next->idx == idx)
					(*head)->tail = (*head)->begin->next;
			} else
				(*head)->begin = tmp;
		}
	}
}

void addNumAtEnd(simpList_t * restrict * restrict head, const float data){
	if ((*head)->type == string) {
		printf("\nError: Incorrect type of list\n");
		return;
	
	} else {
		node_t *newNode = (node_t*)calloc(1,sizeof(node_t));
		++(*head)->size;

		if (!(*head)->begin) {
			(*head)->tail = newNode;
			(*head)->tail->idx = (*head)->size;
			(*head)->tail->data = (float*)calloc(1,sizeof(float));
			*(float*)(*head)->tail->data = data;
			(*head)->begin = (*head)->tail;
	
		} else {
			(*head)->tail->next = newNode;
			(*head)->tail->next->idx = (*head)->size;
			(*head)->tail->next->data = (float*)calloc(1,sizeof(float));
			*(float*)(*head)->tail->next->data = data;
			(*head)->tail = (*head)->tail->next;
		}
	}
}

void addNumAtBegining(simpList_t * restrict * restrict head, const float data){
	if ((*head)->type == string) {
		printf("\nError: Incorrect type of list\n");
		return;
	
	} else {
		node_t * restrict newNode = (node_t*)calloc(1,sizeof(node_t)), 
			* restrict aux = NULL;
		++(*head)->size;

		if (!(*head)->begin) {
			(*head)->begin = newNode;
			(*head)->begin->idx = (*head)->size;
			(*head)->begin->data = (float*)calloc(1,sizeof(float));
			*(float*)(*head)->begin->data = data;
			(*head)->tail = (*head)->begin;

		} else { 	
			aux = (*head)->begin;
			(*head)->begin = newNode;
			(*head)->begin->idx = (*head)->size;
			(*head)->begin->data = (float*)calloc(1,sizeof(float));
			*(float*)(*head)->begin->data = data;
			(*head)->begin->next = aux;
		}
	}
}

void addNumAtPosition(simpList_t * restrict * restrict head, 
	const int32_t idx, const float data){
	if ((*head)->type == string) {
		printf("\nError: Incorrect type of list\n");
		return;
	
	} else {
		bool exist = false;
		node_t * restrict aux = NULL, * restrict tmp = (*head)->begin;

		if (!(*head)->begin)
			return;
	
		else {
			while ((*head)->begin->idx != idx && (*head)->begin)
				(*head)->begin = (*head)->begin->next;

			if ((*head)->begin)
				exist = true;

			if (exist) {
				++(*head)->size;
				aux = (*head)->begin->next;
				(*head)->begin->next = (node_t*)calloc(1,sizeof(node_t));
				(*head)->begin->next->data = 
					(float*)calloc(1,sizeof(float));
				*(float*)(*head)->begin->next->data = data;
				(*head)->begin->next->idx = (*head)->size;
				(*head)->begin->next->next = aux;
				(*head)->begin = tmp;

				if ((*head)->begin->next->idx == idx)
					(*head)->tail = (*head)->begin->next;
			} else
				(*head)->begin = tmp;
		}
	}
}

void printStr(simpList_t * restrict gInit){
	if (gInit->type == real) {
		printf("\nError: Incorrect type of list\n");
		return;
	
	} else {
		node_t * restrict aux = gInit->begin;
		printf("\n\nAddresses and contents of the list:\n");

		while (aux) {
			printf("\tNode %d: %s -> %p\n",aux->idx,(char*)aux->data,aux);
			aux = aux->next;
		}
	}
}

void printNum(simpList_t * restrict gInit, const int32_t dec){
	if (gInit->type == string) {
		printf("\nError: Incorrect type of list\n");
		return;

	} else {
		node_t * restrict aux = gInit->begin;
		printf("\n\nAddresses and contents of the list:\n");

		while (aux) {
			printf("\tNode %d: %.*f -> %p\n",aux->idx,dec,*(float*)aux->data,aux);
			aux = aux->next;
		}
	}
}

//Restar uno al indice antes de enviarlo como parametro
void deleteNode(simpList_t * restrict * restrict head, const int32_t idx){
	node_t * restrict tmp = (*head)->begin, * restrict aux = NULL;

	if (!tmp) //Si lista vacia
		return;

	while ((*head)->begin && (*head)->begin->idx != idx) {
		aux = (*head)->begin; //Nodo anterior al que se quiere borrar
		(*head)->begin = (*head)->begin->next; //Nodo a borrar
	}

	if (!aux) {//Si primer nodo
		tmp = (*head)->begin->next;
		free((*head)->begin);
	
	} else if (!(*head)->begin->next) { //En caso del ultimo nodo
		free(aux->next);
		aux->next = NULL;

	} else { //Caso general
		aux->next = aux->next->next;
		//Se liga al nodo siguiente del que se quiere borrar
		free((*head)->begin);
	}

	--(*head)->size;
	(*head)->begin = tmp;
}

void cleanList(simpList_t * restrict gInit){
	node_t * restrict aux = gInit->begin, * restrict tmp;

	printf("\nGetting free nodes:\n");

	while (aux) {
		//printf("\tRelease node at address: %p\n",aux);
		free(aux->data);
		tmp = aux;
		aux = aux->next;
		free(tmp);
	}
	printf("\nAll nodes released\n");
}

void destroyList(simpList_t * restrict gInit){
	free(gInit);
	printf("\nList destroyed\n");
}

void reverse(simpList_t * restrict * restrict head){
	node_t * restrict refTail = (*head)->tail; 
	//Guarda referencia de la cola

	for (register int_fast32_t i = 0; i < (*head)->size; i++){	
		node_t * restrict aux = (*head)->begin, * restrict tmp = NULL;
		//Se toma el valor de la cola como pivote
		//Camibia a nodo siguiente
		for ( ; aux != (*head)->tail; aux = aux->next)
			tmp = aux; //Nodo anterior

		(*head)->tail = tmp; //Se ligan los nodos en el nuevo orden
		aux->next = tmp; 
	}

	(*head)->tail = (*head)->begin;
	(*head)->begin = refTail; //Se convierte cola en cabeza
}

void reindex(simpList_t * restrict * restrict head){
	node_t * restrict aux = (*head)->begin;
	(*head)->size = 0;

	while (aux) {
		aux->idx = ++(*head)->size;
		aux = aux->next;
	}
}

node_t *searchNode(simpList_t * restrict gInit, const int32_t idx){
	node_t * restrict aux = gInit->begin;

	while (aux->next && aux->idx != idx)
		aux = aux->next;

	return aux;
}

//Ordenamiento sin qsort()
void mergeSort(simpList_t * restrict * restrict head){
	if ((*head)->begin)
		if ((*head)->type == string)
			mergeSortStr(&(*head)->begin);

		else
			mergeSortNum(&(*head)->begin);

	else 
		printf("\nEmpty list cannot be reordered\n");
}

void mergeSortNum(node_t * restrict * restrict headRef){
	node_t * restrict head = *headRef, * restrict a = NULL,
		* restrict b = NULL;

	if (!head || !head->next)
		return;

	frontBackSplit(head, &a, &b);
	mergeSortNum(&a);
	mergeSortNum(&b);

	*headRef = sortedMergeNum(a,b);
}

void mergeSortStr(node_t * restrict * restrict headRef){
	node_t * restrict head = *headRef, * restrict a = NULL,
		* restrict b = NULL;

	if (!head || !head->next)
		return;

	frontBackSplit(head, &a, &b);
	mergeSortStr(&a);
	mergeSortStr(&b);

	*headRef = sortedMergeStr(a,b);
}

void frontBackSplit(node_t * restrict head, node_t * restrict * restrict headRef, 
		node_t * restrict * restrict tailRef){

	node_t * restrict fast = NULL, * restrict slow = NULL;

	if (!head || !head->next) {
		*headRef = head;
		*tailRef = NULL;
	
	} else {
		slow = head;
		fast = head->next;
	}

	while (fast) {
		fast = fast->next;

		if (fast) {
			slow = slow->next;
			fast = fast->next;
		}
	}

	*headRef = head;
	*tailRef = slow->next;
	slow->next = NULL;
}


node_t *sortedMergeNum(node_t * restrict a, node_t * restrict b){
	if (!a)
		return b;

	else if (!b)
		return a;

	if (*(float*)a->data <= *(float*)b->data) {
		a->next = sortedMergeNum(a->next,b);
		return a;
	
	} else {
		b->next = sortedMergeNum(a,b->next);
		return b;
	}
}

node_t *sortedMergeStr(node_t * restrict a, node_t * restrict b){
	if (!a)
		return b;

	else if (!b)
		return a;

	if (strcmp((const char*)a->data, (const char*)b->data) < 0) {
		a->next = sortedMergeStr(a->next,b);
		return a;
	
	} else {
		b->next = sortedMergeStr(a,b->next);
		return b;
	}
}