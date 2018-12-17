/*
Compilacion con: 
gcc -Wall -std=c11 -O3 -march=native firstUseList.c -Wl,--stack,335544320

* Se marcan hasta 320MB (bytes en el comando) de stack disponibles para la ejecucion
*/

//Definicion de funciones
static simpList_t *createList(int32_t val){
	simpList_t * restrict newList = NULL;
	
	if ((newList = (simpList_t*)calloc(0x1,sizeof(simpList_t)))) {
		newList->type = (!val) ? string : real;
		return newList;

	} else 
		return NULL;
}

static void *assignData(void * restrict data, int32_t val){
	void * restrict toAssign = NULL;

	if (!val) {
		toAssign = calloc((strlen((const char*)data)+0x1), sizeof(char));
		strcpy((char*)toAssign, (const char*)data);

	} else {
		toAssign = calloc(0x1,sizeof(float));
		*(float*)toAssign = *(float*)data;
	}

	return toAssign; 
}

static bool addStrAtEnd(simpList_t * restrict * restrict head, const char * restrict data){
	if(!head) //Valida la no entrada de valores nulos
		return true; //Si hubo error

	if ((*head)->type) {
		printf("\nError: Incorrect type of list\n");
		return true; 
	
	} else {
		char * restrict newData = (char*)assignData((void*)data, string);
		node_t * restrict newNode = createNode();

		if (newNode && newData) {

			++(*head)->size;

			if (!(*head)->begin) {
				(*head)->tail = newNode;
				(*head)->tail->idx = (*head)->size;
				(*head)->tail->data = newData;
				(*head)->begin = (*head)->tail;
	
			} else {
				(*head)->tail->next = newNode;
				(*head)->tail->next->idx = (*head)->size;
				(*head)->tail->next->data = newData;
				(*head)->tail = (*head)->tail->next;
			}

			return false; //No hubo error
		
		} else if (!newData){
			free(newNode);
			return true;

		} else {
			free(newData);
			return true;
		}
	}
}

static bool addStrAtBegining(simpList_t * restrict * restrict head, 
		const char * restrict data){
	if(!head)
		return true;

	if ((*head)->type) {
		printf("\nError: Incorrect type of list\n");
		return true;
	
	} else {
		char * restrict newData = (char*)assignData((void*)data, string);
		node_t * restrict aux = NULL, * restrict newNode = createNode();

		if (newNode && newData) {
			++(*head)->size;

			if (!(*head)->begin) {
				(*head)->begin = newNode;
				(*head)->begin->idx = (*head)->size;
				(*head)->begin->data = newData;
				(*head)->tail = (*head)->begin;

			} else { 	
				aux = (*head)->begin;
				(*head)->begin = newNode;
				(*head)->begin->idx = (*head)->size;
				(*head)->begin->data = newData;
				(*head)->begin->next = aux;
			}

			return false;

		} else if (!newData) {
			free(newNode);
			return true;

		} else {
			free(newData);
			return true;
		}
	}
}

static bool addStrAtPosition(simpList_t * restrict * restrict head, const int32_t idx,
		const char * restrict data){
	if (!head)
		return true;

	if ((*head)->type) {
		printf("\nError: Incorrect type of list\n");
		return true;
	
	} else {
		char * restrict newData = (char*)assignData((void*)data, string);
		register node_t * restrict aux = NULL, * restrict tmp = (*head)->begin, 
			* restrict newNode = createNode();

		if (newNode && newData) {
			while ((*head)->begin && (*head)->begin->idx < idx)
				(*head)->begin = (*head)->begin->next;

			++(*head)->size;
		
			if ((*head)->begin && (*head)->begin->next) {
				aux = (*head)->begin->next;
				(*head)->begin->next = newNode;
				(*head)->begin->next->data = newData;
				(*head)->begin->next->idx = (*head)->size;
				(*head)->begin->next->next = aux;
				(*head)->begin = tmp;
				return false;

			} else if (!(*head)->begin->next) {
				(*head)->tail->next = newNode;
				(*head)->tail->next->data = newData;
				(*head)->tail->next->idx = (*head)->size;
				(*head)->tail = (*head)->tail->next;
				(*head)->begin = tmp;
				return false;
		
			} else {
				--(*head)->size;
				(*head)->begin = tmp;
				return true;
			}
		
		} else if (!newData){
			free(newNode);
			return true;

		} else {
			free(newData);
			return true;
		}
	}
}


static bool addNumAtEnd(simpList_t * restrict * restrict head, const float data){
	if (!head)
		return true;

	if (!(*head)->type) {
		printf("\nError: Incorrect type of list\n");
		return true;
	
	} else {
		float * restrict newData = (float*)assignData((void*)&data, real);
		node_t * restrict newNode = createNode();

		if (newNode && newData) {
			++(*head)->size;

			if (!(*head)->begin) {
				(*head)->tail = newNode;
				(*head)->tail->idx = (*head)->size;
				(*head)->tail->data = newData;
				(*head)->begin = (*head)->tail;
	
			} else {
				(*head)->tail->next = newNode;
				(*head)->tail->next->idx = (*head)->size;
				(*head)->tail->next->data = newData;
				(*head)->tail = (*head)->tail->next;
			}

			return false;

		} else if (!newData){
			free(newNode);
			return true;

		} else {
			free(newData);
			return true;
		}
	}
}

static bool addNumAtBegining(simpList_t * restrict * restrict head, const float data){
	if (!head)
		return true;

	if (!(*head)->type) {
		printf("\nError: Incorrect type of list\n");
		return true;
	
	} else {
		float * restrict newData = (float*)assignData((void*)&data, real);
		node_t * restrict aux = NULL, * restrict newNode = createNode();

		if (newNode && newData) {
			++(*head)->size;

			if (!(*head)->begin) {
				(*head)->begin = newNode;
				(*head)->begin->idx = (*head)->size;
				(*head)->begin->data = newData;
				(*head)->tail = (*head)->begin;

			} else { 	
				aux = (*head)->begin;
				(*head)->begin = newNode;
				(*head)->begin->idx = (*head)->size;
				(*head)->begin->data = newData;
				(*head)->begin->next = aux;
			}

			return false;

		} else if (!newData){
			free(newNode);
			return true;

		} else {
			free(newData);
			return true;
		}
	}
}

static bool addNumAtPosition(simpList_t * restrict * restrict head, const int32_t idx,
		const float data){
	if(!head)
		return true;

	if (!(*head)->type) {
		printf("\nError: Incorrect type of list\n");
		return true;
	
	} else {
		float * restrict newData = (float*)assignData((void*)&data, real);
		node_t * restrict aux = NULL, * restrict tmp = (*head)->begin, 
			* restrict newNode = createNode();

		if (newNode && newData) {

			while ((*head)->begin && (*head)->begin->idx != idx)
				(*head)->begin = (*head)->begin->next;

			++(*head)->size;

			if ((*head)->begin && (*head)->begin->next) {
				aux = (*head)->begin->next;
				(*head)->begin->next = newNode;
				(*head)->begin->next->data = newData;
				(*head)->begin->next->idx = (*head)->size;
				(*head)->begin->next->next = aux;
				(*head)->begin = tmp;
				return false;

			} else if (!(*head)->begin->next) {
				(*head)->tail->next = newNode;
				(*head)->tail->next->data = newData;
				(*head)->tail->next->idx = (*head)->size;
				(*head)->tail = (*head)->tail->next;
				(*head)->begin = tmp;
				return false;
		
			} else {
				--(*head)->size;
				(*head)->begin = tmp;
				return true;
			}

		} else if (!newData){
			free(newNode);
			return true;

		} else {
			free(newData);
			return true;
		}
	}
}


static bool printList(simpList_t * restrict gInit, int32_t dec){
	if (!gInit || !gInit->begin)
		return true;

	node_t * restrict aux = gInit->begin;

	if (!gInit->type) {
		while (aux) {
			printf("\tNode %d: %s -> %p\n",aux->idx, (char*)aux->data, (void*)aux);
			aux = aux->next;
		}
	
	} else {
		while (aux) {
			printf("\tNode %d: %.*f -> %p\n",aux->idx,dec, *(float*)aux->data, 
				(void*)aux);
			aux = aux->next;
		}
	}

	return false;
}

static bool deleteNodeByIndex(simpList_t * restrict * restrict head, const int32_t idx){
	if (!head || !(*head)->begin) //Si lista vacia o nula
		return true;

	else {
		register node_t * restrict tmp = NULL, * restrict aux = (*head)->begin;

		while (aux && aux->idx != idx) {
			tmp = aux; //Nodo anterior al que se quiere borrar
			aux = aux->next; //Nodo a borrar
		}

		if (aux->idx == idx) {
			if (!tmp) {//Si primer nodo
				(*head)->begin = aux->next;
				free(aux->data);
				free(aux);
	
			} else if (!aux->next) { //En caso del ultimo nodo
				free(aux->data);
				free(aux);
				tmp->next = NULL;

			} else { //Caso general
				//Se liga al nodo siguiente del que se quiere borrar
				tmp->next = tmp->next->next;
				free(aux->data);
				free(aux);
			}

			--(*head)->size;

			return false;
		
		} else //Si no encuentra un nodo a borrar
			return true;
	}
}

static bool deleteNodeByStr(simpList_t * restrict * restrict head, 
		const char * restrict data){
	if (!head || !(*head)->begin)
		return true;

	else {
		register node_t * restrict aux = (*head)->begin;

		if ((*head)->type) {
			printf("\nError: Incorrect type of list\n");
			return true;

		} else 
			while (aux && strcmp((const char*)aux->data, data))
				aux = aux->next;

		return !aux || deleteNodeByIndex(head,aux->idx);
	}
}

static bool deleteNodeByNum(simpList_t * restrict * restrict head, const float data){
	if (!head || !(*head)->begin)
		return true;

	else {
		register node_t * restrict aux = (*head)->begin;

		if (!(*head)->type) {
			printf("\nError: Incorrect type of list\n");
			return true;

		} else
			while (aux && *(float*)aux->data != data) 
				aux = aux->next;

		return !aux || deleteNodeByIndex(head,aux->idx);
	}
}

static void cleanList(simpList_t * restrict gInit){
	if (!gInit || !gInit->begin)
		return;

	else {
		node_t * restrict tmp;

		printf("\nGetting free nodes:\n");

		for (register node_t * restrict aux = gInit->begin; aux; free(tmp)) {
			tmp = aux;
			aux = aux->next;
			free(tmp->data);
		}

		printf("\nAll nodes released\n");
	}
}

static bool reverse(simpList_t * restrict * restrict head){
	if (!head || !(*head)->begin)
		return true;
	
	else {
		node_t * restrict refTail = (*head)->tail; 
		//Guarda referencia de la cola

		for (register int_fast32_t i = 0; i < (*head)->size; i++){	
			register node_t * restrict aux = (*head)->begin, * restrict tmp = NULL;
			//Se toma el valor de la cola como pivote
			//Camibia a nodo siguiente
			for ( ; aux != (*head)->tail; aux = aux->next)
				tmp = aux; //Nodo anterior

			(*head)->tail = tmp; //Se ligan los nodos en el nuevo orden
			aux->next = tmp; 
		}

		(*head)->tail = (*head)->begin;
		(*head)->begin = refTail; //Se convierte cola en cabeza

		return false;
	}
}

static bool reindex(simpList_t * restrict * restrict head){
	if (!head || !(*head)->begin)
		return true;

	else {
		register node_t * restrict aux = (*head)->begin;
		(*head)->size = 0;

		while (aux) {
			aux->idx = ++(*head)->size;
			aux = aux->next;
		}

		return false;
	}
}

node_t *searchNode(simpList_t * restrict gInit, const int32_t idx){
	if (!gInit || !gInit->begin)
		return NULL;
	
	else {
		node_t * restrict aux = gInit->begin;

		while (aux->next && aux->idx != idx)
			aux = aux->next;

		return aux;
	}
}

static bool mergeSort(simpList_t * restrict * restrict head){
	if (!head || !(*head)->begin) {
		printf("\nEmpty list cannot be reordered\n");
		return true;
	
	} else {
		pthread_mutex_init(&mtx,NULL);

		if (!(*head)->type)
			mergeSortStr(&(*head)->begin);

		else 
			mergeSortNum(&(*head)->begin);

		pthread_mutex_destroy(&mtx);		

		return false;
	}
}

static node_t *splitList(node_t * restrict head){
	register node_t * restrict fast = head->next, * restrict slow = head;

	pthread_mutex_lock(&mtx);
	while (fast->next && fast->next->next) {
		fast = fast->next->next;
		slow = slow->next;
	}
	pthread_mutex_unlock(&mtx);

	return slow;
}

static void mergeSortStr(node_t * restrict * restrict headRef){
	node_t * restrict a = NULL, * restrict b = NULL;

	if (!headRef || !(*headRef)->next)
		return;

	a = splitList(*headRef); //Obtiene el nodo de la mitad
	b = a->next; //Se obtiene la cabeza de la segunda lista
	a->next = NULL; //Partimos la lista finalizandola con un NULL
	a = *headRef; //Se coloca el inicio de la lista en el nodo A

	if (!inUse) {
		inUse = true; //Variables que limitan la creacion de nuevos hilos a 2

		pthread_create(&thr[0], NULL, (void*)mergeSortStr, (void * restrict)&a);
		pthread_create(&thr[1], NULL, (void*)mergeSortStr, (void * restrict)&b);
				
		for (register int_fast32_t i = 0; i < THREADS; i++)
			pthread_join(thr[i], NULL);

		inUse = false;

	} else {
		mergeSortStr(&a); //Se hace recursion
		mergeSortStr(&b);
	}

	*headRef = sortedMergeStr(a,b);
}

static void mergeSortNum(node_t * restrict * restrict headRef){
	node_t * restrict a = NULL, * restrict b = NULL;

	if (!headRef || !(*headRef)->next)
		return;

	a = splitList(*headRef);
	b = a->next;
	a->next = NULL;
	a = *headRef;

	if (!inUse) {
		inUse = true;

		pthread_create(&thr[0], NULL, (void*)mergeSortNum, (void * restrict)&a);
		pthread_create(&thr[1], NULL, (void*)mergeSortNum, (void * restrict)&b);
						
		for (register int_fast32_t i = 0; i < THREADS; i++)
			pthread_join(thr[i], NULL);

		inUse = false;

	} else {
		mergeSortNum(&a); //Se hace recursion
		mergeSortNum(&b);	
	}

	*headRef = sortedMergeNum(a,b);
}

static node_t *sortedMergeStr(node_t * restrict a, node_t * restrict b){
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

static node_t *sortedMergeNum(node_t * restrict a, node_t * restrict b){
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
