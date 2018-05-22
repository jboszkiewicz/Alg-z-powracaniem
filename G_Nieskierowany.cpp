#include "G_Nieskierowany.h"
//macierz s¹siedztwa
std::list<int> cyklMS;
void GNS_Hamilton(bool **macierz, int n){

}
void FindEuler(int v, bool **macierz, int n){
	bool empty = false;
	//while(!empty){
		for(int i = 0; i < n; i++){
			if(macierz[v][i]){
				macierz[v][i] = 0;
				macierz[i][v] = 0;
				FindEuler(i, macierz, n);
			}
		}

//	}
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