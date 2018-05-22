#include "G_Skierowany.h"
#include "G_Nieskierowany.h"
#include "Generator.h"
#include <ctime>
#include <chrono>
#include <iostream>
#include <string>
#include <math.h>
#include <list>

using tp = std::chrono::time_point<std::chrono::system_clock>; //do pomiaru czasu

void MStoLN(bool **MS, std::list<int> *LN, int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(MS[i][j]){
				LN[i].push_back(j);
			}
		}
	}
}

int main(){
	setlocale(LC_ALL, "polish");
	srand((unsigned)time(NULL));
	bool isCorrectAnswer = false;
	int answer, type, liczbaWierzcho�k�w, liczbaKraw�dzi, stopie�Nasycenia;
	tp start, end;
	std::string wynik;

	bool ** macierzS�siedztwa = NULL;
	std::list<int> *listaNast�pnik�w = NULL;
	while(true){ //p�tla g��wna programu
		isCorrectAnswer = false;
		while(true){
			puts("Podaj ilo�� wierzcho�k�w: ");
			if(!scanf_s("%d", &liczbaWierzcho�k�w) || liczbaWierzcho�k�w < 1)
				puts("Incorrect answer. Try again.");
			else break;
		}
		while(true){
			puts("Podaj wsp�czynnik nasycenia wierzcho�kami z zakresu 10-90: ");
			if(!scanf_s("%d", &stopie�Nasycenia) || !(stopie�Nasycenia >= 10 && stopie�Nasycenia <= 90))
				puts("Incorrect answer. Try again.");
			else break;
		}
		
		liczbaKraw�dzi = (int)ceil((liczbaWierzcho�k�w*(liczbaWierzcho�k�w - 1) / 2.0) * (stopie�Nasycenia / 100.0));
		isCorrectAnswer = false;

		while(!isCorrectAnswer){
			printf("\nWybierz typ grafu:\n");
			printf("   '1' - Graf nieskierowany;\n");
			printf("   '2' - Graf skierowany;\n");

			scanf_s("%d", &type);
			switch(type){
				case 1:// Graf nieskierowany

					macierzS�siedztwa = new bool*[liczbaWierzcho�k�w];
					for(int i = 0; i < liczbaWierzcho�k�w; i++){
						macierzS�siedztwa[i] = new bool[liczbaWierzcho�k�w];
						for(int j = 0; j < liczbaWierzcho�k�w; j++)
							macierzS�siedztwa[i][j] = 0;
					}
					GenerateGraphMS(macierzS�siedztwa, liczbaWierzcho�k�w, liczbaKraw�dzi);
					for(int i = 0; i < liczbaWierzcho�k�w; i++){
						for(int j = 0; j < liczbaWierzcho�k�w; j++)
							printf("%d ", macierzS�siedztwa[i][j]);
						printf("\n");
					}
					isCorrectAnswer = true;
					break;
				case 2:// // Graf skierowany
					listaNast�pnik�w = new std::list<int>[liczbaWierzcho�k�w];
					GenerateGraphLN(listaNast�pnik�w, liczbaWierzcho�k�w, liczbaKraw�dzi);
					isCorrectAnswer = true;
					for(int i = 0; i < liczbaWierzcho�k�w; i++){
						printf("%d ->: ", i);
						for(std::list<int>::iterator j = listaNast�pnik�w[i].begin(); j != listaNast�pnik�w[i].end(); j++){
							printf("%d ", *j);
						}
						printf("\n");
					}
					break;
				default:
					printf("Incorrect answer. Try again.");
					break;
			}
		}

		isCorrectAnswer = false;

		while(!isCorrectAnswer){
			printf("\nCo chcesz zrobi� z grafem:\n");
			printf("  1  Znajd� cykl Hamiltona z wykorzystaniem algorytmu Robersta-Floresa;\n");
			printf("  2  Znajd� cykl Eulera z wykorzystaniem algorytmu Fleury'ego;\n");
			printf("  3  Nowy graf;\n");
			printf("  4  Zako�cz;\n");

			printf("Give your answer:");
			scanf_s("%d", &answer);

			if(type == 1){// Graf Nieskierowany
				switch(answer){
					case 1://algorytm Robersta-Floresa (cykl Hamiltona)
						start = std::chrono::system_clock::now();
						
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(MS DFS): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 2://algorytm Fleury'ego (cykl Eulera)
						start = std::chrono::system_clock::now();
						if(IsEulerianMS(macierzS�siedztwa, liczbaWierzcho�k�w)){
							GNS_Euler(macierzS�siedztwa, liczbaWierzcho�k�w);
						} else{//nie posiada cyklu
							printf("Graf nie posiada cyklu\n");
						}
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(MS DEL): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 3:
						isCorrectAnswer = true;
						for(int i = 0; i < liczbaWierzcho�k�w; ++i)
							delete[] macierzS�siedztwa[i];
						delete[] macierzS�siedztwa;
						break;
					case 4:
						printf("Exited");
						return 0;
					default:
						printf("Incorrect answer. Try again.");
						break;
				}
			} else{//Graf Skierowany
				switch(answer){
					case 1://algorytm Robersta-Floresa (cykl Hamiltona)
						start = std::chrono::system_clock::now();
						
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(MG DFS): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 2://algorytm Fleury'ego (cykl Eulera)
						start = std::chrono::system_clock::now();
						if(liczbaKraw�dzi >= liczbaWierzcho�k�w){
							GS_Euler(listaNast�pnik�w, liczbaWierzcho�k�w);	
						} else{//nie posiada cyklu
							printf("Graf nie posiada cyklu Eulera");
						}
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(MG DEL): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 3:
						isCorrectAnswer = true;
						delete[] listaNast�pnik�w;
						break;
					case 4:
						printf("Exited");
						return 0;
					default:
						printf("Incorrect answer. Try again.");
						break;
				}
			}
		}
	}

	return 0;
}

