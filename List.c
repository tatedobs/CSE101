#include<stdio.h>
#include<stdlib.h>

#include "List.h"

typedef struct NodeObj {
	int data;
	struct NodeObj* prev;
	struct NodeObj* next;
} NodeObj;

typedef NodeObj* Node;


typedef struct ListObj {
	Node head;
	Node foot;
	Node cursor;
	int length;
	int index;
} ListObj;




Node newNode(int data) {
	Node N = malloc(sizeof(NodeObj));
	N -> data = data;
	N -> next = NULL;
	N -> prev = NULL;
	return(N);
}




void freeNode(Node* pN) {
	if(pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}



List newList(void) {
	List L = malloc(sizeof(ListObj));
	L -> head = NULL;
	L -> foot = NULL;
	L -> cursor = NULL;
	L -> index = -1;
	L -> length = 0;
	return(L);
}




void freeList(List* pL) {
	if(pL != NULL && *pL != NULL) {
		while(length(*pL) > 0) {
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}





int length(List L) {
	if(L != NULL) {
		return(L -> length);
	} else {
		printf("ERROR: length() cannot be called on NULL List\n");
		exit(EXIT_FAILURE);
	}
}



int index(List L) {
	if(L != NULL) {
		return(L -> index);
	} else {
		printf("ERROR: index() cannot be called on NULL List\n");
		exit(EXIT_FAILURE);
	}
}




int head(List L) {
	if(L != NULL && length(L) != 0) {
		return(L -> head -> data);
	} else {
		printf("ERROR: head() cannot be called on NULL or empty List\n");
		exit(EXIT_FAILURE);
	}
}




int foot(List L) {
	if(L != NULL && length(L) != 0) {
		return(L -> foot -> data);
	} else {
		printf("ERROR: foot() cannot be called on NULL or empty List\n");
		exit(EXIT_FAILURE);
	}
}




int get(List L) {
	if(L != NULL && length(L) != 0) {
		return(L -> cursor -> data);
	} else {
		printf("ERROR: get() cannot be called on NULL or empty List\n");
		exit(EXIT_FAILURE);
	}
}



int equals(List A, List B) {
	if(A == NULL || B == NULL) {
		printf("ERROR: equals() cannot be called on NULL Lists\n");
	}

	if(A -> length != B -> length) {
		return 0;
	}

	Node tempA = B -> head;
	Node tempB = A -> head;
	while(tempA -> next != NULL && tempB -> next != NULL) {
		if(tempA -> data != tempB -> data) {
			return 0;
		}
		tempA = tempA -> next;
		tempB = tempB -> next;
	}
	return 1;
}





void clear(List L) {
	L -> head = NULL;
	L -> foot = NULL;
	L -> cursor = NULL;
	L -> length = 0;
	L -> index = -1;
}



void moveFront(List L) {
	if(length(L) > 0) {
		L -> cursor = L -> head;
		L -> index = 0;
	}
}



void moveBack(List L) {
	if(length(L) > 0) {
		L -> cursor = L -> foot;
		L -> index = L -> length - 1;
	}
}




void movePrev(List L) {
	if(L -> cursor != NULL) {
		L -> cursor = L -> cursor -> prev;
		L -> index--;
	}
}




void moveNext(List L) {
	if(L -> cursor != NULL) {
		if(L -> cursor == L -> foot) {
			L -> cursor = NULL;
			L -> index = -1;
		} else {
			L -> cursor = L -> cursor -> next;
			L -> index++;
		}
	}
}




void prepend(List L, int data) {
	Node N = newNode(data);

	if(L -> head == NULL) {
		L -> head = N;
		L -> foot = N;
	} else {
		L -> head -> prev = N;
		N -> next = L -> head;
		L -> head = N;
		L -> index++;
	}

	L -> length++;
}





void append(List L, int data) {
	Node N = newNode(data);

	if(L -> head == NULL) {
		L -> head = N;
		L -> foot = N;
	} else {
		L -> foot -> next = N;
		N -> prev = L -> foot;
		L -> foot = N;
	}
	L -> length++;
}




void insertBefore(List L, int data) {
	Node N = newNode(data);

	if(L != NULL && length(L) > 0) {
		N -> next = L -> cursor;
		N -> prev = L -> cursor -> prev;

		if(L -> cursor != L -> head) {
			L -> cursor -> prev -> next = N;
		} else {
			L -> head = N;
		}

		L -> cursor -> prev = N;

		L -> index++;
		L -> length++;
	} else {
		printf("ERROR: insertBefore() cannot be called on NULL or empty List\n");
		exit(EXIT_FAILURE);
	}
}




void insertAfter(List L, int data) {
	Node N = newNode(data);

	if(L != NULL && length(L) > 0) {
		N -> prev = L -> cursor;
		N -> next = L -> cursor -> next;

		if(L -> cursor != L -> foot) {
			L -> cursor -> next -> prev = N;
		} else {
			L -> foot = N;
		}

		L -> cursor -> next = N;

		L -> length++;
	} else {
		printf("ERROR: insertAfter() cannot be called on NULL or empty List\n");
		exit(EXIT_FAILURE);
	}
}




void deleteFront(List L) {
	if(L != NULL && length(L) != 0) {
		Node N = NULL;

		if(L -> cursor == L -> head) {
			L -> index = -1;
			L -> cursor = NULL;
		}

		N = L -> head;
		L -> head = L -> head -> next;
		L -> length--;

		freeNode(&N);
	} else {
		printf("ERROR: deleteFront() cannot be called on NULL or empty List\n");
		exit(EXIT_FAILURE);
	}
}



void deleteBack(List L) {
	if(L != NULL && length(L) > 0) {
		Node N = NULL;

		if(L -> cursor == L -> foot) {
			L -> index = -1;
			L -> cursor = NULL;
		}

		N = L -> foot;
		L -> foot = L -> head -> prev;
		L -> length--;

		freeNode(&N);
	} else {
		printf("ERROR: deleteBack() cannot be called on NULL or empty List\n");
		exit(EXIT_FAILURE);
	}
}



void delete(List L) {
	if(L != NULL && length(L) > 0) {
		if(L -> cursor == L -> head) {
			deleteFront(L);
		}
		else if(L -> cursor == L -> foot) {
			deleteBack(L);
		}
		else {
			Node N = L -> cursor;
			L -> cursor -> prev -> next = L -> cursor -> next;
			L -> cursor -> next -> prev = L -> cursor -> prev;
			freeNode(&N);
			L -> length--;
			L -> index = -1;
		}
	} else {
		printf("ERROR: delete() cannot be called on NULL or empty List\n");
		exit(EXIT_FAILURE);
	}
}





void printList(FILE* out, List L) {
	Node N = L -> head;
	while(N != NULL) {
		fprintf(out, "%d ", N -> data);
		N = N -> next;
	}
}




List copyList(List L) {
	List C = newList();
	Node N = L -> head;
	while(N != NULL) {
		append(C, N -> data);
		N = N -> next;
	}
	return C;
}