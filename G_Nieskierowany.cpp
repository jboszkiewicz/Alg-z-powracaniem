#include "G_Nieskierowany.h"
//macierz s¹siedztwa
std::list<int> cyklMS;

bool FindHamilton(bool **macierz, int n, bool *visited, int v, int &licznik, int start){
	visited[v] = true;
	cyklMS.push_back(v);
	licznik++;
	if(licznik == n){//warunek wyjœcia z rekurencji
		if(macierz[v][start]){//istnieje ³uk do wierzcho³ka startowego
			cyklMS.push_back(start);
			return true;
		}else{
			licznik--;
			cyklMS.pop_back();
			visited[v] = false;
			return false;
		}
	}
	for(int i = 0; i < n; i++){
		if(macierz[v][i] && !visited[i]){
			if(FindHamilton(macierz, n, visited, i, licznik, start)){
				return true;
			}//else szukaj dalej
		}
	}
	licznik--;
	cyklMS.pop_back();
	visited[v] = false;
	return false;
}

void GNS_Hamilton(bool **macierz, int n){
	cyklMS.clear();
	bool *visited = new bool[n];
	for(int i = 0; i < n; i++)
		visited[i] = false;
	
	bool found = false;
	int licznik;
	for(int i = 0; i < n; i++){
		licznik = 0;
		if(FindHamilton(macierz, n, visited, i, licznik, i)){
			found = true;
			break;
		}
	}
	if(found){//wypisanie
		printf("Cykl Hamiltona: ");
		for(std::list<int>::iterator i = cyklMS.begin(); i != cyklMS.end(); i++){
			printf("%d ", *i);
		}
		printf("\n");
	} else{
		printf("Nie znaleziono cyklu Hamiltona :(\n");
	}
}
void FindEuler(int v, bool **macierz, int n){
	for(int i = 0; i < n; i++){
		if(macierz[v][i]){
			macierz[v][i] = 0;
			macierz[i][v] = 0;
			FindEuler(i, macierz, n);
		}
	}
	cyklMS.push_front(v);
}

void GNS_Euler(bool **macierz, int n){//cykl Eulera
	bool **kopia = new bool*[n];
	for(int i = 0; i < n; i++){
		kopia[i] = new bool[n];
		for(int j = 0; j < n; j++){
			kopia[i][j] = macierz[i][j];
		}
	}
	cyklMS.clear();
	FindEuler(0, kopia, n);

	printf("Cykl Eulera: ");
	for(std::list<int>::iterator i = cyklMS.begin(); i != cyklMS.end(); i++){
		printf("%d ", *i);
	}
	printf("\n");
}