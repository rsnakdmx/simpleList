#include "simpleList.h"
#include "shareUtil.h"
#include <time.h>

#define NODOS 4000000
#define STRING 30

int main(void) {
	char try[STRING] = {'\0'};
	clock_t tBegin = clock(), tQuick;
	node_t *aux = NULL;
	simpList_t *ap = createList(string);
	simpList_t *ap1 = createList(real);

	printf("La lista esta vacia? %s\n", (isEmpty(ap)) ? "Si" : "No");

	printf("\nLista de cadenas: ");

	addStrAtEnd(&ap,"A"); //ERROR: Se pierde el primer nodo de la lista
	//Corregido, la funcion deleteNode solo borraba el nodo, mas no sus datos
	addStrAtEnd(&ap, "Ju");
	addStrAtEnd(&ap, "-");
	addStrAtEnd(&ap, "li");
	//addNumAtEnd(&ap, 10); //Muestra error
	//printList(ap,0);
	reverse(&ap);
	addStrAtBegining(&ap, "-");
	//printList(ap,0);
	addStrAtPosition(&ap, 3, "Oh");
	addStrAtPosition(&ap, 2, "!");
	addStrAtPosition(&ap, 5, "!");
	addStrAtBegining(&ap, "sS");

	printf("\nLa lista esta vacia? %s\n", (isEmpty(ap)) ? "Si" : "No");

	for (register int_fast32_t i = 0; i < NODOS; ++i)
		addStrAtEnd(&ap, randString(try,(size_t)rand()%30));
	
	printf("\nAntes de mergesort:");
	//printList(ap,0); //Corregido error en el que no se imprimian cadenas de chars
	tQuick = clock();
	mergeSort(&ap);
	printf("\n\nEl tiempo de mergesort es: %lf segundos\n",
		(double)(clock() - tQuick)/CLOCKS_PER_SEC);
	printf("\nDespues de mergesort:");
	//printList(ap,0);
	aux = searchNode(NULL,3);

	if (aux)
		printf("\nEl nodo %d tiene %s -> %p\n\n",aux->idx, (char*)aux->data, (void*)aux);
	
	printf("\nCambiando los indices de la lista:");
	reindex(&ap);
	printf("\nBorrando los nodos 1, 7 con Ju\n");
	deleteNodeByIndex(&ap,1);
	deleteNodeByIndex(&ap,7);
	deleteNodeByStr(&ap,"Ju");
	//printList(ap,0);
	printf("\nLa lista tiene: %d nodos que miden: %d\n",getSize(ap),
		(int32_t)sizeof(node_t));
	printf("\nLa lista abarca en memoria (sin considerar cadenas): %lf GB\n",
		(double)(getSize(ap)*sizeof(node_t))/(1024*1024*1024));
	cleanList(ap);

	destroyList(ap);

	printf("\n\nLista de numeros: ");
	addNumAtBegining(&ap1, 61.23);
	addNumAtEnd(&ap1, 5.3);
	addNumAtEnd(&ap1, 9.4);
	addNumAtEnd(&ap1, 1005.69);
	addNumAtPosition(&ap1, 1, 850.666);
	addNumAtPosition(&ap1, 4, 777.965);
	addNumAtEnd(&ap1, 66397.69);
	//printList(ap1,4);
	reverse(&ap1);
	addNumAtBegining(&ap1, 789.1);
	//printList(ap1,3);
	addNumAtPosition(&ap1, 3, 85);
	addNumAtPosition(&ap1, 2, 4.4);
	addNumAtPosition(&ap1, 5, 1.7);
	addNumAtPosition(&ap1, 1, 985.17);
	//printList(ap1,3);
	
	aux = searchNode(ap1,0);
	
	if (aux)
		printf("\nEl nodo %d tiene %f -> %p\n\n",ap1->tail->idx, 
			*(float*)ap1->tail->data, (void*)ap1->tail);

	for (register int_fast32_t i = 0; i < NODOS; ++i){
		srand(rdtsc());
		addNumAtEnd(&ap1, (float)((rand()%500)*(rand()%500)));
	}
	
	printf("\nAntes de mergesort:");
	//printList(ap1,2);
	tQuick = clock();
	mergeSort(&ap1);
	printf("\n\nEl tiempo de mergesort es: %lf segundos\n",
		(double)(clock() - tQuick)/CLOCKS_PER_SEC);
	printf("\nDespues de mergesort:");
	//printList(ap1,1);
	
	printf("\nLa lista tiene: %d nodos\n",getSize(ap1));
	printf("\nCambiando los indices de la lista:");
	reindex(&ap1);
	printf("\nBorrando los nodos 1 y 4\n");
	deleteNodeByIndex(&ap1,1);
	deleteNodeByIndex(&ap1,4);
	deleteNodeByNum(&ap1,66398);
	deleteNodeByNum(&ap1,66397.69);
	//printList(ap1,0);
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