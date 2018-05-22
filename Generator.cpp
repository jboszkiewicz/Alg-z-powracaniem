#include "Generator.h"
#include <stdlib.h>

void GenerateGraphMS(bool **macierz, int v, int e){
	int i, x, y, start;
	bool *hasEdge = new bool[v];
	for(int a = 0; a < v; a++)
		hasEdge[a] = 0;
	i = 0;
	int n = v;
	start = x = rand() % v;
	while(i < e - 1){
		y = rand() % v;
		if(x != y && !macierz[x][y]){
			if(i == e - 3){
				if(y == start)
					continue;
			}
			if(i == e - 2){//przedostatnia kraw�d�
				if(y == start)
					continue;
				if(macierz[y][start]){
					continue;
				}
			}
			if( n > 0 && hasEdge[y]){// && !listaNast�pnik�w[y].empty()){//istniej� wierzcho�ki nieposiadaj�ce nast�pnika, wylosowany posiada ( dla n==1 tylko x nie posiada nast�pnika )	  
			//	if(n > 1 && e != v + 1)
				continue;//losuj inny
			}
			macierz[x][y] = 1;
			macierz[y][x] = 1;
			hasEdge[y] = true;
			x = y;
			i++;
			n--;
		}
	}
	macierz[start][y] = 1;
	macierz[y][start] = 1;
}

bool IsEulerianMS(bool **macierz, int n){
	int liczbaKraaw�dzi;
	for(int x = 0; x < n; x++){
		liczbaKraaw�dzi = 0;
		for(int y = 0; y < n; y++){
			if(macierz[x][y])
				liczbaKraaw�dzi++;
		}
		if(liczbaKraaw�dzi % 2){
			printf("nieparzysty stopie�\n");
			return false;
		}
		if(liczbaKraaw�dzi == 0){
			printf("brak kraw�dzi");
			return false;
		}
	}
	return true;
}

void GenerateGraphLN(std::list<int> *listaNast�pnik�w, int v, int e){
	int i, x, y, start;
	std::list<int>::iterator w;
	int n = v;
	i = 0;
	start = x = rand() % v;
	while(i < e - 1){
		y = rand() % v;
		if(x != y){
			if(i == e - 2 && y == start)//przedostatnia kraw�d�
				continue;
			if(n > 1 && !listaNast�pnik�w[y].empty()){//istniej� wierzcho�ki nieposiadaj�ce nast�pnika, wylosowany posiada ( dla n==1 tylko x nie posiada nast�pnika )
		//		if(n > 2 && e != v + 1)
				continue;//losuj inny
			}
			bool kraw�d�Istnieje = false;
			for(w = listaNast�pnik�w[x].begin(); w != listaNast�pnik�w[x].end(); w++){
				if(*w == y){
					kraw�d�Istnieje = true;
					break;
				}
			}
			if(!kraw�d�Istnieje){
				if(i == e - 2){
					bool kraw�d�Istnieje = false;
					for(w = listaNast�pnik�w[y].begin(); w != listaNast�pnik�w[y].end(); w++){//czy istnieje kraw�d� z wierzcho�ka y do pocz�tkowego
						if(*w == start){
							kraw�d�Istnieje = true;
							break;
						}
					}
					if(kraw�d�Istnieje)//je�li tak, losuj inny wierzcho�ek
						continue;
				}
				listaNast�pnik�w[x].push_back(y);
				i++;
				x = y;
				n--;
			}
		}
	}
	listaNast�pnik�w[y].push_back(start);
}

bool IsEulerianLN(std::list<int> *lista, int n){
	int *stopnie = new int[n];
	std::list<int>::iterator iterator;
	for(int i = 0; i < n; i++){
		if(lista[i].size() == 0){
			printf("wierzcho�ek ko�cowy\n");
			return false;
		}
		stopnie[i] = lista[i].size();
	}

	for(int i = 0; i < n; i++){
		for(iterator = lista[i].begin(); iterator != lista[i].end(); iterator++){
			stopnie[*iterator]--;
		}
	}
	for(int i = 0; i < n; i++){
		if(stopnie[i]){
			printf("niezgodno�� stopni wierzcho�ka\n");
			return false;
		}
	}
	return true;
}