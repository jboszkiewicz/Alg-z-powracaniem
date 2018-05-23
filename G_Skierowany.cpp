#include "G_Skierowany.h"
//lista nastêpników
std::list<int> cyklLN;

bool FindHamilton(std::list<int> *lista, int n, bool *visited, int v, int &licznik, int start){
	visited[v] = true;
	cyklLN.push_back(v);
	licznik++;
	if(licznik == n){//warunek wyjœcia z rekurencji
		for(std::list<int>::iterator i = lista[v].begin(); i != lista[v].end(); i++){
			if(*i == start){
				cyklLN.push_back(start);
				return true;
			}
		}
		licznik--;
		cyklLN.pop_back();
		visited[v] = false;
		return false;
	}
	for(std::list<int>::iterator i = lista[v].begin(); i != lista[v].end(); i++){
		if(!visited[*i]){
			if(FindHamilton(lista, n, visited, *i, licznik, start)){
				return true;
			}//else szukaj dalej
		}
	}
	licznik--;
	cyklLN.pop_back();
	visited[v] = false;
	return false;
}

void GS_Hamilton(std::list<int> *lista, int n){
	cyklLN.clear();
	bool *visited = new bool[n];
	for(int i = 0; i < n; i++)
		visited[i] = false;

	bool found = false;
	int licznik;
	for(int i = 0; i < n; i++){
		licznik = 0;
		if(FindHamilton(lista, n, visited, i, licznik, i)){
			found = true;
			break;
		}
	}
	if(found){//wypisanie
		printf("Cykl Hamiltona: ");
		for(std::list<int>::iterator i = cyklLN.begin(); i != cyklLN.end(); i++){
			printf("%d ", *i);
		}
		printf("\n");
	} else{
		printf("Nie znaleziono cyklu Hamiltona :(\n");
	}
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

