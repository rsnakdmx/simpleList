void mergeSort(node_t * restrict * restrict headRef){
	node_t * restrict head = headRef;
	node_t * restrict a;
	node_t * restrict b;

	if (!head || !head->next)
		return;

	frontBackSplit(head, &a, &b);
	mergeSort(&a);
	mergeSort(&b);

	*headRef = sortedMerge(a,b);
}

void frontBackSplit(node_t * restrict head, node_t * restrict * restrict headRef, node_t * restrict * restrict tailRef){

	node_t * restrict fast;
	node_t * restrict slow;

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


node_t *sortedMerge(node_t * restrict a, node_t * restrict b){
	if (!a)
		return b;

	else if (!b)
		return a;

	if (strcmp((const char*)a->data, (const char*)b->next) < 0) {
		a->next = sortedMerge(a->next,b);
		return a;
	
	} else {
		b->next = sortedMerge(a,b->next);
		return b;
	}
}