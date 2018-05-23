#include "Generator.h"
#include <stdlib.h>

void GenerateGraphMS(bool **macierz, int v, int e){
	int i, x, y;
	i = 0;
	//start = x = rand() % v;
	while(i < e){
		x = rand() % v;
		y = rand() % v;
		if(x != y && !macierz[x][y]){
			macierz[x][y] = 1;
			macierz[y][x] = 1;
			i++;
		}
	}
}

bool IsEulerianMS(bool **macierz, int n){
	int liczbaKrawêdzi;
	for(int x = 0; x < n; x++){
		liczbaKrawêdzi = 0;
		for(int y = 0; y < n; y++){
			if(macierz[x][y])
				liczbaKrawêdzi++;
		}
		if(liczbaKrawêdzi % 2){
		//	printf("nieparzysty stopieñ\n");
			return false;
		}
	}
	return true;
}

void GenerateGraphLN(std::list<int> *listaNastêpników, int v, int e){
	int i, x, y;
	std::list<int>::iterator w;
	i = 0;
	while(i < e){
		x = rand() % v;
		y = rand() % v;
		bool krawêdŸIstnieje = false;
		for(w = listaNastêpników[x].begin(); w != listaNastêpników[x].end(); w++){
			if(*w == y){
				krawêdŸIstnieje = true;
				break;
			}
		}
		if(x != y && !krawêdŸIstnieje){
			listaNastêpników[x].push_back(y);
			i++;
		}
	}
}

bool IsEulerianLN(std::list<int> *lista, int n){
	int *stopnie = new int[n];
	std::list<int>::iterator iterator;
	for(int i = 0; i < n; i++){
		stopnie[i] = lista[i].size();
	}

	for(int i = 0; i < n; i++){
		for(iterator = lista[i].begin(); iterator != lista[i].end(); iterator++){
			stopnie[*iterator]--;
		}
	}
	for(int i = 0; i < n; i++){
		if(stopnie[i]){
	//		printf("niezgodnoœæ stopni wierzcho³ka\n");
			return false;
		}
	}
	return true;
}