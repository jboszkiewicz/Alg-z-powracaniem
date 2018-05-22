#include "G_Skierowany.h"
//lista nastêpników
std::list<int> cyklLN;

void GS_Hamilton(std::list<int> *lista, int n){

}




void FindEuler(int v, std::list<int> *lista){
	while(!lista[v].empty()){
		int x = lista[v].front();
		lista[v].pop_front();
		FindEuler(x, lista);
	}
	cyklLN.push_front(v);
}

void GS_Euler(std::list<int> *lista, int n){
	std::list<int> *kopia = new std::list<int>[n];
	for(int i = 0; i < n; i++)
		kopia[i] = lista[i];
	cyklLN.clear();
	FindEuler(0, lista);
	
	printf("Cykl Eulera: ");
	for(std::list<int>::iterator i = cyklLN.begin(); i != cyklLN.end(); i++){
		printf("%d ", *i);
	}
	printf("\n");
}

