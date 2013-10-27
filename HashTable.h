// Autor: Matei Razvan-Madalin 313CA

#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include"LinkedList.h"

template<typename Tkey, typename Tvalue>
struct info_elem {
	Tkey key;
	LinkedList<Tvalue> values; // list of sites;
};

/**Functia de hash*/
unsigned hashFunction(char* key) {
	unsigned hash = 5381;

	for (unsigned i=0; i<strlen(key); i++)
		hash = ((hash << 5) + hash) + key[i];
	
	return hash;
}

// Variables for load compute
unsigned dimension = 10;
unsigned no_elements = 0;

template<typename Tkey, typename Tvalue>
class HashTable {
public:
	LinkedList<struct info_elem<Tkey, Tvalue> > *H;
	int HMAX;
	unsigned (*hash) (Tkey);
	
	// Constructor
	HashTable(int hmax, unsigned (*h) (Tkey)) {
		HMAX = hmax;
		hash = h;
		H = new LinkedList<struct info_elem<Tkey, Tvalue> >[HMAX];
	}
	
	// Destructor
	~HashTable() { }
	
	// Get new hash of hmax lists
	void Reset(int hmax) {
		HMAX = hmax;
		H = new LinkedList<struct info_elem<Tkey, Tvalue> >[HMAX];
	}
	
	void put(Tkey key, Tvalue value) {
		list_elem<info_elem<Tkey, Tvalue> > *p;
		list_elem<Tvalue> *v;
		info_elem<Tkey, Tvalue> information;
		unsigned hkey;
		
		hkey = hash(key) % HMAX;
		p = H[hkey].pFirst;
		
		while(p != NULL) {
			if(strcmp(key, p->info.key) == 0) {
				break;
			}
			p = p->next;
		}
		
		if(p != NULL){
			v = p->info.values.pFirst;
			while(v != NULL) {
				if(strcmp(value, v->info) == 0) {
					return;
				}
				v = v->next;
			}
			p->info.values.addLast(value);
			no_elements++;
		}
		else {
			information.key = key;
			information.values.addFirst(value);
			H[hkey].addLast(information);
			no_elements++;
		}
	}
	
	void putInOrder(Tkey key, Tvalue value) {
		list_elem<info_elem<Tkey, Tvalue> > *p;
		list_elem<Tvalue> *v;
		info_elem<Tkey, Tvalue> information;
		unsigned hkey;
		
		hkey = hash(key) % HMAX;
		p = H[hkey].pFirst;
		
		while(p != NULL) {
			if(strcmp(key, p->info.key) == 0) {
				break;
			}
			p = p->next;
		}
		
		if(p != NULL){
			v = p->info.values.pFirst;
			while(v != NULL) {
				if(strcmp(value, v->info) == 0) {
					return;
				}
				if(strcmp(value, v->info) > 0) {
					v = v->next;
					continue;
				}
				if(strcmp(value, v->info) < 0) {
					p->info.values.InsertBefore(v, value);
					no_elements++;
					return;
				}
			}
			p->info.values.addLast(value);
			no_elements++;
		}
		else {
			information.key = key;
			information.values.addFirst(value);
			H[hkey].addLast(information);
			no_elements++;
		}
	}
				
	// Put key and entire list
	void putList(Tkey key, LinkedList<Tvalue> v) {

		info_elem<Tkey, Tvalue> information;
		unsigned hkey;
		
		hkey = hash(key) % HMAX;
		
		information.key = key;
		information.values = v;
		H[hkey].addFirst(information);
	}
	
	// Display Hastable
	void dumpI() {
		int i;
		
		printf("===============\n");
		printf("== HashTable ==\n");
		printf("===============\n");
		
		for(i=0; i<HMAX; i++){
			H[i].Sdump();
		}
		printf("===============\n");
		printf("===============\n");
	}
};
	
#endif //_HASHTABLE_H

