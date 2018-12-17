#include "simpleList.h"
#include "shareUtil.h"
#include <time.h>

#define NODOS 10
#define STRING 30

int main(void) {
	char try[STRING] = {'\0'};
	clock_t tBegin = clock(), tQuick;
	node_t *aux = NULL;
	simpList_t *ap = createStrList();
	simpList_t *ap1 = createNumList();

	printf("\nLista de cadenas: ");

	addStrAtEnd(&ap,"A");
	addStrAtEnd(&ap, "Ju");
	addStrAtEnd(&ap, "-");
	addStrAtEnd(&ap, "li");
	//addNumAtEnd(&ap, 10); //Muestra error
	printStr(ap);
	reverse(&ap);
	addStrAtBegining(&ap, "-");
	//printStr(ap);
	addStrAtPosition(&ap, 3, "Oh");
	addStrAtPosition(&ap, 2, "!");
	addStrAtPosition(&ap, 5, "!");
	srand(rdtsc());
	for (register int_fast32_t i = 0; i < NODOS; ++i)
		addStrAtEnd(&ap, randString(try,(size_t)rand()%30));
	printf("\nAntes de quicksort:");
	//printStr(ap); //Corregido error en el que no se imprimian cadenas de chars
	tQuick = clock();
	mergeSort(&ap);
	printf("\n\nEl tiempo de quicksort es: %lf segundos\n",
		(double)(clock() - tQuick)/CLOCKS_PER_SEC);
	printf("\nDespues de quicksort:");
	printStr(ap);
	aux = searchNode(ap,3);
	printf("\nEl nodo %d tiene %s -> %p\n\n",aux->idx, (char*)aux->data, aux);
	printf("\nBorrando el nodo 1\n");
	deleteNode(&ap,1);
	printf("\nCambiando los indices de la lista:");
	reindex(&ap);
	//printStr(ap);
	printf("\nLa lista tiene: %d nodos que miden: %d\n",getSize(ap),
		(int32_t)sizeof(node_t));
	printf("\nLa lista abarca en memoria (sin considerar cadenas): %lf GB\n",
		(double)(getSize(ap)*sizeof(node_t))/(1024*1024*1024));
	cleanList(ap);
	destroyList(ap);

	printf("\n\nLista de numeros: ");
	addNumAtEnd(&ap1, 5.3);
	addNumAtEnd(&ap1, 9.4);
	addNumAtEnd(&ap1, 1005.69);
	addNumAtEnd(&ap1, 66397.69);
	//printNum(ap1,4);
	reverse(&ap1);
	addNumAtBegining(&ap1, 789.1);
	//printNum(ap1,3);
	addNumAtPosition(&ap1, 3, 85);
	addNumAtPosition(&ap1, 2, 4.5);
	addNumAtPosition(&ap1, 5, 1.7);
	srand(rdtsc());
	for (register int_fast32_t i = 0; i < NODOS; ++i)
		addNumAtEnd(&ap1, (float)rand());

	printf("\nAntes de quicksort:");
	//printNum(ap1,2);
	tQuick = clock();
	mergeSort(&ap1);
	printf("\n\nEl tiempo de quicksort es: %lf segundos\n",
		(double)(clock() - tQuick)/CLOCKS_PER_SEC);
	printf("\nDespues de quicksort:");
	printNum(ap1,1);
	aux = searchNode(ap1,3);
	printf("\nEl nodo %d tiene %f -> %p\n\n",aux->idx, *(float*)aux->data, aux);
	printf("\nLa lista tiene: %d nodos\n",getSize(ap1));
	printf("\nBorrando el nodo 1\n");
	deleteNode(&ap1,1);
	printf("\nCambiando los indices de la lista:");
	reindex(&ap1);
	//printNum(ap1,0);
	printf("\nLa lista tiene: %d nodos que miden: %d\n",getSize(ap1),
		(int32_t)sizeof(node_t));
	printf("\nLa lista abarca en memoria: %lf GB\n",
		(double)(getSize(ap1)*sizeof(node_t))/(1024*1024*1024));
	cleanList(ap1);
	destroyList(ap1);

	printf("\n\nEl tiempo transcurrido es: %lf segundos\n",
		(double)(clock() - tBegin)/CLOCKS_PER_SEC);

	return EXIT_SUCCESS;
}