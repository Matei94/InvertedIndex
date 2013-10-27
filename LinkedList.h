// Autor: Matei Razvan-Madalin, 313CA

/* Lista dublu inlantuita */

#include<stdio.h>
#include<stdlib.h>
using namespace std;

#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

template<typename T>
struct list_elem {
	T info;
	struct list_elem *next, *prev;
};

template<typename T>
class LinkedList {
public:
	struct list_elem<T> *pFirst, *pLast;
	
	// Constructor
	LinkedList() {
		pFirst = NULL;
		pLast = NULL;
	}
	
	// Destructor
	~LinkedList() { }
	
	//Manual Destructor
	void clean() {
		struct list_elem<T> *aux;
		
		aux = pFirst;
		while(aux != NULL) {
			free(aux->info);
			aux = aux->next;
		}
	}
	
	void equal(LinkedList<T> &a) {
		struct list_elem<T> *aux;
		
		if(a.isEmpty() == 1) {
			return;
		}
		
		aux = a.pFirst;
		do {
			addLast(strdup(aux->info));
			aux = aux->next;
		} while(aux != NULL);
	}
	
	void reset() {
		pFirst = NULL;
		pLast = NULL;
	}
		
	void addFirst(T x) {
		struct list_elem<T> *aux;
		
		aux = new struct list_elem<T>;
		aux->info = x;
		
		if(pFirst == NULL) { //list is empty
			pFirst = aux;
			pLast = aux; 
			aux->prev = NULL;
			aux->next = NULL;
			return;
		}
		
		if(pFirst != NULL) { //list is not empty
			pFirst->prev = aux;
			aux->next = pFirst;
			aux->prev = NULL;
			pFirst = aux;
		}
	}
	
	void addLast(T x) {
		struct list_elem<T> *aux;
		
		aux = new struct list_elem<T>;
		aux->info = x;
		
		if(pLast == NULL) { //list is empty
			pFirst = aux;
			pLast = aux;
			aux->next = NULL;
			aux->prev = NULL;
			return;
		}
		
		if(pLast != NULL) { //list is not empty
			pLast->next = aux;
			aux->prev = pLast;
			aux->next = NULL;
			pLast = aux;
		}
	}
	
	void InsertBefore(struct list_elem<T>* there, T x) {
		struct list_elem<T> *aux;
		
		aux = new struct list_elem<T>;
		aux->info = x;
		
		aux->next = there;
		aux->prev = there->prev;
		
		if(there->prev != NULL) {
			there->prev->next = aux;
		}
		else { // addFirst;
			pFirst = aux;
		}
		there->prev = aux;
	}
	
	void RemoveThat(struct list_elem<T>* there) {
		if((there == pFirst)&&(there == pLast)) {
			pFirst = NULL;
			pLast = NULL;
			return;
		}
		if(there == pFirst) {
			pFirst = pFirst->next;
			pFirst->prev = NULL;
			return;
		}
		if(there == pLast) {
			pLast = pLast->prev;
			pLast->next = NULL;
			return;
		}
		
		there->prev->next = there->next;
		there->next->prev = there->prev;
	}
	
	void removeFirst() {
		if(pFirst == NULL) {
			printf("\tError 1: List is empty!\n");
			return;
		}
		if(pFirst == pLast) { //1 element
			delete pFirst;
			pFirst = NULL;
			pLast = NULL;
			return;
		}
		if(pFirst != pLast) { //more elements
			struct list_elem<T> *aux;
			aux = pFirst;
			pFirst = aux->next;
			pFirst->prev = NULL;
			delete aux;
			return;
		}
	}
	
	void removeLast() {
		if(pFirst == NULL) {
			printf("\tError 2: List is empty!\n");
			return;
		}
		if(pFirst == pLast) { //1 element
			delete pLast;
			pLast = NULL;
			pFirst = NULL;
			return;
		}
		if(pFirst != pLast) {
			struct list_elem<T> *aux;
			aux = pLast;
			pLast = aux->prev;
			pLast->next = NULL;
			delete aux;
			return;
		}
	}
	
	struct list_elem<T>* findFirstOccurrence(T x) {
		struct list_elem<T> *aux;
		
		aux = pFirst;
		while(aux != NULL) {
			if(aux->info == x) {
				return aux;
			}
			aux = aux->next;
		}
		return NULL;
	}
		
	struct list_elem<T>* findLastOccurrence(T x) {
		struct list_elem<T> *aux;
		
		aux = pLast;
		while(aux != NULL) {
			if(aux->info == x) {
				return aux;
			}
			aux = aux->prev;
		}
		return NULL;
	}
	
	void removeFirstOccurrence(T x) {
		struct list_elem<T> *aux;
		
		aux = findFirstOccurrence(x);
		if(aux != NULL) {
			if(aux == pFirst) {
				removeFirst();
				return;
			}
			if(aux == pLast) {
				removeLast();
				return;
			}
			
			aux->prev->next = aux->next;
			aux->next->prev = aux->prev;
			delete aux;
			return;
		}
		printf("NO occurrence!\n");
	}
	
	void removeLastOccurrence(T x) {
		struct list_elem<T> *aux;
		
		aux = findLastOccurrence(x);
		if(aux != NULL) {
			if(aux == pFirst) {
				removeFirst();
				return;
			}
			if(aux == pLast) {
				removeLast();
				return;
			}
			
			aux->prev->next = aux->next;
			aux->next->prev = aux->prev;
			delete aux;
			return;
		}
		printf("NO occurrence!\n");
	}
			
	int isEmpty() {
		if (pFirst == NULL) {
			return 1; //1 = empty
		}
		return 0;
	}
	
	// Print list
	void Fdump() {
		struct list_elem<T> *aux;
		
		if(isEmpty() == 1) {
			printf("\tEmpty\n");
			return;
		}
		
		aux = pFirst;
		do {
			cout << aux->info << " ";
			aux = aux->next;
		} while(aux != NULL);
	}
	
	// Print HashTable
	void Sdump() {
		struct list_elem<T> *aux;
		struct list_elem<char*> *aux2;
		
		printf("\t__==** LinkedList **==__\n");
		if(isEmpty() == 1) {
			printf("\tEmpty\n");
			return;
		}
		printf("\tNULL => ");
		aux = pFirst;
		do {
			cout << "(" << aux->info.key << " -> [";
			
			aux2 = aux->info.values.pFirst;
			if(aux2 == NULL) {
				cout << "]";
				break;
			}
			else {
				do {
					cout << aux2->info << ", ";
					aux2 = aux2->next;
				} while(aux2 != NULL);
			}
			cout << "]), ";
			
			aux = aux->next;
		} while(aux != NULL);
		printf(" => NULL\n");
	}	
};

#endif //__LINKEDLIST_H

