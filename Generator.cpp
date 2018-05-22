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
			if(i == e - 2){//przedostatnia krawêdŸ
				if(y == start)
					continue;
				if(macierz[y][start]){
					continue;
				}
			}
			if( n > 0 && hasEdge[y]){// && !listaNastêpników[y].empty()){//istniej¹ wierzcho³ki nieposiadaj¹ce nastêpnika, wylosowany posiada ( dla n==1 tylko x nie posiada nastêpnika )	  
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
	int liczbaKraawêdzi;
	for(int x = 0; x < n; x++){
		liczbaKraawêdzi = 0;
		for(int y = 0; y < n; y++){
			if(macierz[x][y])
				liczbaKraawêdzi++;
		}
		if(liczbaKraawêdzi % 2){
			printf("nieparzysty stopieñ\n");
			return false;
		}
		if(liczbaKraawêdzi == 0){
			printf("brak krawêdzi");
			return false;
		}
	}
	return true;
}

void GenerateGraphLN(std::list<int> *listaNastêpników, int v, int e){
	int i, x, y, start;
	std::list<int>::iterator w;
	int n = v;
	i = 0;
	start = x = rand() % v;
	while(i < e - 1){
		y = rand() % v;
		if(x != y){
			if(i == e - 2 && y == start)//przedostatnia krawêdŸ
				continue;
			if(n > 1 && !listaNastêpników[y].empty()){//istniej¹ wierzcho³ki nieposiadaj¹ce nastêpnika, wylosowany posiada ( dla n==1 tylko x nie posiada nastêpnika )
		//		if(n > 2 && e != v + 1)
				continue;//losuj inny
			}
			bool krawêdŸIstnieje = false;
			for(w = listaNastêpników[x].begin(); w != listaNastêpników[x].end(); w++){
				if(*w == y){
					krawêdŸIstnieje = true;
					break;
				}
			}
			if(!krawêdŸIstnieje){
				if(i == e - 2){
					bool krawêdŸIstnieje = false;
					for(w = listaNastêpników[y].begin(); w != listaNastêpników[y].end(); w++){//czy istnieje krawêdŸ z wierzcho³ka y do pocz¹tkowego
						if(*w == start){
							krawêdŸIstnieje = true;
							break;
						}
					}
					if(krawêdŸIstnieje)//jeœli tak, losuj inny wierzcho³ek
						continue;
				}
				listaNastêpników[x].push_back(y);
				i++;
				x = y;
				n--;
			}
		}
	}
	listaNastêpników[y].push_back(start);
}

bool IsEulerianLN(std::list<int> *lista, int n){
	int *stopnie = new int[n];
	std::list<int>::iterator iterator;
	for(int i = 0; i < n; i++){
		if(lista[i].size() == 0){
			printf("wierzcho³ek koñcowy\n");
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
			printf("niezgodnoœæ stopni wierzcho³ka\n");
			return false;
		}
	}
	return true;
}