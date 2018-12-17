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

int32_t cmpStr(const void *a, const void *b){
	return strcmp(*(const char**)a, *(const char**)b);
}

int32_t cmpNum(const void *a, const void *b){
	return *(const float*)a - *(const float*)b;
}

void quicksortStr(simpList_t * restrict * restrict gInit){
	if ((*gInit)->type == real) {
		printf("\nError: Incorrect type of list\n");
		return;
	
	} else {
		char **mPool = 
			(char**)calloc((*gInit)->size,sizeof(char*));
		node_t * restrict auxBegin = (*gInit)->begin;

		for (register int_fast64_t i= 0; i < (*gInit)->size; ++i) {
			mPool[i] = (char*)(*gInit)->begin->data;
			(*gInit)->begin = (*gInit)->begin->next;
		}

		qsort(mPool,(*gInit)->size,sizeof(char*),cmpStr);
		(*gInit)->begin = auxBegin;

		for (register int_fast64_t i= 0; i < (*gInit)->size; ++i) {
			(*gInit)->begin->data = (void*)mPool[i];
			(*gInit)->begin = (*gInit)->begin->next;
		}

		(*gInit)->begin = auxBegin;
		free(mPool);
	}
}

void quicksortNum(simpList_t * restrict * restrict gInit){
	if ((*gInit)->type == string) {
		printf("\nError: Incorrect type of list\n");
		return;
	
	} else {
		float *mPool = 
			(float*)calloc((*gInit)->size,sizeof(float));
		node_t * restrict auxBegin = (*gInit)->begin;
	
		for (register int_fast32_t i= 0; i < (*gInit)->size; ++i) {
			mPool[i] = *(float*)(*gInit)->begin->data;
			(*gInit)->begin = (*gInit)->begin->next;
		}

		qsort(mPool,(*gInit)->size,sizeof(float),cmpNum);
		(*gInit)->begin = auxBegin;

		for (register int_fast32_t i= 0; i < (*gInit)->size; ++i) {
			*(float*)(*gInit)->begin->data = mPool[i];
			(*gInit)->begin = (*gInit)->begin->next;
		}

		(*gInit)->begin = auxBegin;
		free(mPool);
	}
}