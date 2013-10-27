// algorithm.h : 
// Schelet cod Tema 3 SD - Inverted index
// Autor: octavian.rinciog@gmail.com
// Adaugari: Matei Razvan Madalin, 313CA

#ifndef _ALGORITHM_H
#define _ALGORITHM_H 1

#include<string>
#include "HashTable.h"

class Algorithm {
public:
	
	// Constructor
	Algorithm(void) { } 

	// Destructor
	~Algorithm(void){ }


	// PUT
	void indexSite(const std::string &row, HashTable<char*, char*> &hid, HashTable<char*, char*> &hid2) {
		char *row_tok=strdup(row.c_str());
	
		char *command=strtok(row_tok," "); 
		if (strcmp(command,"PUT")!=0) {
			return;
		}
	
		char *site=strtok(NULL," ");
		char *word=strtok(NULL," ");

		while(word) {
			if(isspace(word[0])) break; // ignore empty spaces.
		
			// Test if hash capacity is over 0.7
			if((float)no_elements / dimension < 0.7) {
				hid.putInOrder(strdup(word), strdup(site));
			}
			else {
				dimension *= 2; // double hastable dimension.
				hid2.Reset(dimension);
		
				list_elem< info_elem<char*, char*> > *vKey;
				unsigned i;
	
				for(i=0; i < dimension/2; i++) {
					vKey = hid.H[i].pFirst;
					while(vKey != NULL) {
						hid2.putList(vKey->info.key, vKey->info.values);
						vKey = vKey->next;
					}
				}
		
				hid.H = hid2.H;
				hid.HMAX = dimension;
			
				hid.putInOrder(strdup(word), strdup(site));
			}
		
			word=strtok(NULL," ");
		}
	}


	// GET
	void getSites(const std::string &row, HashTable<char*, char*> &hid) {
		list_elem<info_elem<char*, char*> > *p;
		list_elem<char*> *v, *r;
		LinkedList<char*> *result;
		result = new LinkedList<char*>;
		unsigned hkey;
		char first_time = 1;
		int donot;
	
		int ind = 0, i;
		char **words;
		words = new char*[100];
	
		// Entire command.
		char *row_tok=strdup(row.c_str());

		char *command = strtok(row_tok," ");
		if (strcmp(command,"GET") != 0) {
			return;
		}
	
		char *word=strtok(NULL," ");

		while(word) {
			if(isspace(word[0])) break; // ignore empty spaces.
		
			// Ignore if already tested.
			for(i = 0; i<ind; i++) {
				if(strcmp(word, words[i]) == 0) {
					continue;
				}
			}
		
			words[ind] = strdup(word);
			ind++;
		
			hkey = hid.hash(word) % hid.HMAX;
			p = hid.H[hkey].pFirst;
		
			while(p != NULL) {
				if(strcmp(word, p->info.key) == 0) {
					break;
				}
				p = p->next;
			}
		
			if(p == NULL) {
				cout << "SITE_NOT_FOUND" << endl;
				return;
			}
			else {
				if(first_time == 1) {
					result->equal(p->info.values);
					first_time = 0;
				}
				else {
					v = p->info.values.pFirst;
					r = result->pFirst;
				
					donot = 0;
					while(r != NULL) {
						while(v != NULL) {
							if(strcmp(v->info, r->info) > 0) {
								if(result->pFirst == result->pLast) {
									cout << "SITE_NOT_FOUND" << endl;
									return;
								}
							
								// Remove Element
								if(r != result->pFirst) {
									r = r->prev;
									result->RemoveThat(r->next);
								}
								else {
									result->removeFirst();
								}
								break;
							}
					
							if(strcmp(v->info, r->info) < 0) {
								v = v->next;
								continue;
							}
					
							if(strcmp(v->info, r->info) == 0) {
								v = v->next;
								// Last element in result
								if(r->next == result->pLast->next) {
									donot=1;
								}
								if(v == NULL) {
									r = r->next;
								}
								break;
							}	
						}	
						
							if(v == NULL) {
								if(donot == 1) break;
								if(r->prev != NULL) {
									result->pLast = r->prev;
									result->pLast->next = NULL;
									break;
								}
								else {
									cout << "SITE_NOT_FOUND" << endl;
									return;
								}
							}
							else {
								r = r->next;
							}
					}
				
					if(result->isEmpty() == 1) {
						cout << "SITE_NOT_FOUND" << endl;
						return;
					}
				}
			}	
		
			word=strtok(NULL," ");
		}
	
		result->Fdump();
		cout<<endl;
	}

	// SITE
	void wordInSite(const std::string &row, HashTable<char*, char*> &hid) {
		list_elem<info_elem<char*, char*> > *p;
		list_elem<char*> *v;
		unsigned hkey;
	
		char *row_tok=strdup(row.c_str());
	
		char *command=strtok(row_tok," ");
		if (strcmp(command,"SITE") != 0) {
			return;
		}

		char *site=strtok(NULL," ");
		char *word=strtok(NULL," ");

		while(word) {
			if(isspace(word[0])) break; // ignore empty spaces.
	
			hkey = hid.hash(word) % hid.HMAX;
			p = hid.H[hkey].pFirst;
		
			while(p != NULL) {
				if(strcmp(word, p->info.key) == 0) {
					break;
				}
				p = p->next;
			}
		
			if(p != NULL){
				v = p->info.values.pFirst;
				while(v != NULL) {
					if(strcmp(site, v->info) == 0) {
						break;
					}
					v = v->next;
				}
				if(v == NULL) {	
					cout << "WORD_NOT_FOUND" << endl;
					return;
				}
			}
			else {
				cout << "WORD_NOT_FOUND" << endl;
				return;
			}
	
			word=strtok(NULL," ");
		}
	
		cout << "WORD_FOUND" << endl;
	}

	void resolve() {
		HashTable<char*, char*> hid(10, hashFunction); // battlefield.
		HashTable<char*, char*> hid2(dimension, hashFunction); // auxiliar.
	
		string row;
		while ( std::cin.good() ) {
			std::getline(std::cin,row);
			//nu iau in considerare linii cu mai putin de 3 caractere
			if (row.size()<3)
				continue;
			switch(row[0]) {
			//PUT
			case 'P':
				indexSite(row, hid, hid2);
				break;
			//GET
			case 'G':
				getSites(row, hid);
				break;
			//SITE
			case 'S':
				wordInSite(row, hid);
				break;
			default:
				cout<<"Invalid option"<<endl;
			}
		}
	}

};

#endif
