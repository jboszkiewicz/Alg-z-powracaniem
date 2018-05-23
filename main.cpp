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
	//	int graf = 0;
		isCorrectAnswer = false;
		while(true){
		//	puts("Wybierz graf (1-A, 2-B, 3-C, 4-D): ");
		//	if(!scanf_s("%d", &graf) || !(graf >= 1 && graf <= 4))
		//		puts("Incorrect answer. Try again.");
		//	else break;
		//}
		//liczbaWierzcho�k�w = 5;
		//liczbaKraw�dzi = 6;
		//switch(graf){
		//	case 1:
		//		macierzS�siedztwa = new bool*[liczbaWierzcho�k�w];
		//		for(int i = 0; i < liczbaWierzcho�k�w; i++){
		//			macierzS�siedztwa[i] = new bool[liczbaWierzcho�k�w];
		//			for(int j = 0; j < liczbaWierzcho�k�w; j++)
		//				macierzS�siedztwa[i][j] = 0;
		//		}
		//		macierzS�siedztwa[4][0] = macierzS�siedztwa[0][4] = 1;
		//		macierzS�siedztwa[1][0] = macierzS�siedztwa[0][1] = 1;
		//		macierzS�siedztwa[1][4] = macierzS�siedztwa[4][1] = 1;
		//		macierzS�siedztwa[4][3] = macierzS�siedztwa[3][4] = 1;
		//		macierzS�siedztwa[4][2] = macierzS�siedztwa[2][4] = 1;
		//		macierzS�siedztwa[3][2] = macierzS�siedztwa[2][3] = 1;
		//		
		//		type = 1;
		//		break;
		//	case 2:
		//		macierzS�siedztwa = new bool*[liczbaWierzcho�k�w];
		//		for(int i = 0; i < liczbaWierzcho�k�w; i++){
		//			macierzS�siedztwa[i] = new bool[liczbaWierzcho�k�w];
		//			for(int j = 0; j < liczbaWierzcho�k�w; j++)
		//				macierzS�siedztwa[i][j] = 0;
		//		}
		//		macierzS�siedztwa[1][0] = macierzS�siedztwa[0][1] = 1;//
		//		macierzS�siedztwa[1][2] = macierzS�siedztwa[2][1] = 1;//
		//		macierzS�siedztwa[1][3] = macierzS�siedztwa[3][1] = 1;//
		//		macierzS�siedztwa[4][3] = macierzS�siedztwa[3][4] = 1;//
		//		macierzS�siedztwa[4][2] = macierzS�siedztwa[2][4] = 1;//
		//		macierzS�siedztwa[3][0] = macierzS�siedztwa[0][3] = 1;//
		//		type = 1;
		//		break;
		//	case 3:
		//		listaNast�pnik�w = new std::list<int>[liczbaWierzcho�k�w];
		//		listaNast�pnik�w[0].push_back(3);
		//		listaNast�pnik�w[3].push_back(4);
		//		listaNast�pnik�w[4].push_back(0);
		//		listaNast�pnik�w[4].push_back(2);
		//		listaNast�pnik�w[2].push_back(1);
		//		listaNast�pnik�w[1].push_back(4);
		//		type = 2;
		//		break;
		//	case 4:
		//		listaNast�pnik�w = new std::list<int>[liczbaWierzcho�k�w];
		//		listaNast�pnik�w[0].push_back(1);
		//		listaNast�pnik�w[1].push_back(2);
		//		listaNast�pnik�w[1].push_back(3);
		//		listaNast�pnik�w[3].push_back(4);
		//		listaNast�pnik�w[4].push_back(2);
		//		listaNast�pnik�w[2].push_back(0);
		//		type = 2;
		//		break;
		//}

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

				/*	for(int i = 0; i < liczbaWierzcho�k�w; i++){
						for(int j = 0; j < liczbaWierzcho�k�w; j++)
							printf("%d ", macierzS�siedztwa[i][j]);
						printf("\n");
					}*/

					isCorrectAnswer = true;
					break;
				case 2:// // Graf skierowany
					listaNast�pnik�w = new std::list<int>[liczbaWierzcho�k�w];
					GenerateGraphLN(listaNast�pnik�w, liczbaWierzcho�k�w, liczbaKraw�dzi);
					isCorrectAnswer = true;

					/*for(int i = 0; i < liczbaWierzcho�k�w; i++){
						printf("%d ->: ", i);
						for(std::list<int>::iterator j = listaNast�pnik�w[i].begin(); j != listaNast�pnik�w[i].end(); j++){
							printf("%d ", *j);
						}
						printf("\n");
					}*/

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
						GNS_Hamilton(macierzS�siedztwa, liczbaWierzcho�k�w);
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(GNS Hamilton): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 2://algorytm Fleury'ego (cykl Eulera)
						start = std::chrono::system_clock::now();
						if(IsEulerianMS(macierzS�siedztwa, liczbaWierzcho�k�w)){
							GNS_Euler(macierzS�siedztwa, liczbaWierzcho�k�w);
						} else{//nie posiada cyklu
							printf("Graf nie posiada cyklu Eulera\n");
						}
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(GNS Euler): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
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
						GS_Hamilton(listaNast�pnik�w, liczbaWierzcho�k�w);
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(GS Hamilton): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 2://algorytm Fleury'ego (cykl Eulera)
						start = std::chrono::system_clock::now();
						if(IsEulerianLN(listaNast�pnik�w, liczbaWierzcho�k�w)){
							GS_Euler(listaNast�pnik�w, liczbaWierzcho�k�w);	
						} else{//nie posiada cyklu
							printf("Graf nie posiada cyklu Eulera");
						}
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(GS Euler): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
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

