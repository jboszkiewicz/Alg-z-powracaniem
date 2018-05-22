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
	int answer, type, liczbaWierzcho³ków, liczbaKrawêdzi, stopieñNasycenia;
	tp start, end;
	std::string wynik;

	bool ** macierzS¹siedztwa = NULL;
	std::list<int> *listaNastêpników = NULL;
	while(true){ //pêtla g³ówna programu
		isCorrectAnswer = false;
		while(true){
			puts("Podaj iloœæ wierzcho³ków: ");
			if(!scanf_s("%d", &liczbaWierzcho³ków) || liczbaWierzcho³ków < 1)
				puts("Incorrect answer. Try again.");
			else break;
		}
		while(true){
			puts("Podaj wspó³czynnik nasycenia wierzcho³kami z zakresu 10-90: ");
			if(!scanf_s("%d", &stopieñNasycenia) || !(stopieñNasycenia >= 10 && stopieñNasycenia <= 90))
				puts("Incorrect answer. Try again.");
			else break;
		}
		
		liczbaKrawêdzi = (int)ceil((liczbaWierzcho³ków*(liczbaWierzcho³ków - 1) / 2.0) * (stopieñNasycenia / 100.0));
		isCorrectAnswer = false;

		while(!isCorrectAnswer){
			printf("\nWybierz typ grafu:\n");
			printf("   '1' - Graf nieskierowany;\n");
			printf("   '2' - Graf skierowany;\n");

			scanf_s("%d", &type);
			switch(type){
				case 1:// Graf nieskierowany

					macierzS¹siedztwa = new bool*[liczbaWierzcho³ków];
					for(int i = 0; i < liczbaWierzcho³ków; i++){
						macierzS¹siedztwa[i] = new bool[liczbaWierzcho³ków];
						for(int j = 0; j < liczbaWierzcho³ków; j++)
							macierzS¹siedztwa[i][j] = 0;
					}
					GenerateGraphMS(macierzS¹siedztwa, liczbaWierzcho³ków, liczbaKrawêdzi);
					for(int i = 0; i < liczbaWierzcho³ków; i++){
						for(int j = 0; j < liczbaWierzcho³ków; j++)
							printf("%d ", macierzS¹siedztwa[i][j]);
						printf("\n");
					}
					isCorrectAnswer = true;
					break;
				case 2:// // Graf skierowany
					listaNastêpników = new std::list<int>[liczbaWierzcho³ków];
					GenerateGraphLN(listaNastêpników, liczbaWierzcho³ków, liczbaKrawêdzi);
					isCorrectAnswer = true;
					for(int i = 0; i < liczbaWierzcho³ków; i++){
						printf("%d ->: ", i);
						for(std::list<int>::iterator j = listaNastêpników[i].begin(); j != listaNastêpników[i].end(); j++){
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
			printf("\nCo chcesz zrobiæ z grafem:\n");
			printf("  1  ZnajdŸ cykl Hamiltona z wykorzystaniem algorytmu Robersta-Floresa;\n");
			printf("  2  ZnajdŸ cykl Eulera z wykorzystaniem algorytmu Fleury'ego;\n");
			printf("  3  Nowy graf;\n");
			printf("  4  Zakoñcz;\n");

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
						if(IsEulerianMS(macierzS¹siedztwa, liczbaWierzcho³ków)){
							GNS_Euler(macierzS¹siedztwa, liczbaWierzcho³ków);
						} else{//nie posiada cyklu
							printf("Graf nie posiada cyklu\n");
						}
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(MS DEL): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 3:
						isCorrectAnswer = true;
						for(int i = 0; i < liczbaWierzcho³ków; ++i)
							delete[] macierzS¹siedztwa[i];
						delete[] macierzS¹siedztwa;
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
						if(liczbaKrawêdzi >= liczbaWierzcho³ków){
							GS_Euler(listaNastêpników, liczbaWierzcho³ków);	
						} else{//nie posiada cyklu
							printf("Graf nie posiada cyklu Eulera");
						}
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(MG DEL): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 3:
						isCorrectAnswer = true;
						delete[] listaNastêpników;
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

