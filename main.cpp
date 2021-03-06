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
	int answer, type, liczbaWierzchołków, liczbaKrawędzi, stopieńNasycenia;
	tp start, end;
	std::string wynik;

	bool ** macierzSąsiedztwa = NULL;
	std::list<int> *listaNastępników = NULL;
	while(true){ //pętla główna programu
	//	int graf = 0;
		isCorrectAnswer = false;
		while(true){
		//	puts("Wybierz graf (1-A, 2-B, 3-C, 4-D): ");
		//	if(!scanf_s("%d", &graf) || !(graf >= 1 && graf <= 4))
		//		puts("Incorrect answer. Try again.");
		//	else break;
		//}
		//liczbaWierzchołków = 5;
		//liczbaKrawędzi = 6;
		//switch(graf){
		//	case 1:
		//		macierzSąsiedztwa = new bool*[liczbaWierzchołków];
		//		for(int i = 0; i < liczbaWierzchołków; i++){
		//			macierzSąsiedztwa[i] = new bool[liczbaWierzchołków];
		//			for(int j = 0; j < liczbaWierzchołków; j++)
		//				macierzSąsiedztwa[i][j] = 0;
		//		}
		//		macierzSąsiedztwa[4][0] = macierzSąsiedztwa[0][4] = 1;
		//		macierzSąsiedztwa[1][0] = macierzSąsiedztwa[0][1] = 1;
		//		macierzSąsiedztwa[1][4] = macierzSąsiedztwa[4][1] = 1;
		//		macierzSąsiedztwa[4][3] = macierzSąsiedztwa[3][4] = 1;
		//		macierzSąsiedztwa[4][2] = macierzSąsiedztwa[2][4] = 1;
		//		macierzSąsiedztwa[3][2] = macierzSąsiedztwa[2][3] = 1;
		//		
		//		type = 1;
		//		break;
		//	case 2:
		//		macierzSąsiedztwa = new bool*[liczbaWierzchołków];
		//		for(int i = 0; i < liczbaWierzchołków; i++){
		//			macierzSąsiedztwa[i] = new bool[liczbaWierzchołków];
		//			for(int j = 0; j < liczbaWierzchołków; j++)
		//				macierzSąsiedztwa[i][j] = 0;
		//		}
		//		macierzSąsiedztwa[1][0] = macierzSąsiedztwa[0][1] = 1;//
		//		macierzSąsiedztwa[1][2] = macierzSąsiedztwa[2][1] = 1;//
		//		macierzSąsiedztwa[1][3] = macierzSąsiedztwa[3][1] = 1;//
		//		macierzSąsiedztwa[4][3] = macierzSąsiedztwa[3][4] = 1;//
		//		macierzSąsiedztwa[4][2] = macierzSąsiedztwa[2][4] = 1;//
		//		macierzSąsiedztwa[3][0] = macierzSąsiedztwa[0][3] = 1;//
		//		type = 1;
		//		break;
		//	case 3:
		//		listaNastępników = new std::list<int>[liczbaWierzchołków];
		//		listaNastępników[0].push_back(3);
		//		listaNastępników[3].push_back(4);
		//		listaNastępników[4].push_back(0);
		//		listaNastępników[4].push_back(2);
		//		listaNastępników[2].push_back(1);
		//		listaNastępników[1].push_back(4);
		//		type = 2;
		//		break;
		//	case 4:
		//		listaNastępników = new std::list<int>[liczbaWierzchołków];
		//		listaNastępników[0].push_back(1);
		//		listaNastępników[1].push_back(2);
		//		listaNastępników[1].push_back(3);
		//		listaNastępników[3].push_back(4);
		//		listaNastępników[4].push_back(2);
		//		listaNastępników[2].push_back(0);
		//		type = 2;
		//		break;
		//}

			puts("Podaj ilość wierzchołków: ");
			if(!scanf_s("%d", &liczbaWierzchołków) || liczbaWierzchołków < 1)
				puts("Incorrect answer. Try again.");
			else break;
		}
		while(true){
			puts("Podaj współczynnik nasycenia wierzchołkami z zakresu 10-90: ");
			if(!scanf_s("%d", &stopieńNasycenia) || !(stopieńNasycenia >= 10 && stopieńNasycenia <= 90))
				puts("Incorrect answer. Try again.");
			else break;
		}
		
		liczbaKrawędzi = (int)ceil((liczbaWierzchołków*(liczbaWierzchołków - 1) / 2.0) * (stopieńNasycenia / 100.0));
		isCorrectAnswer = false;

		while(!isCorrectAnswer){
			printf("\nWybierz typ grafu:\n");
			printf("   '1' - Graf nieskierowany;\n");
			printf("   '2' - Graf skierowany;\n");

			scanf_s("%d", &type);
			switch(type){
				case 1:// Graf nieskierowany

					macierzSąsiedztwa = new bool*[liczbaWierzchołków];
					for(int i = 0; i < liczbaWierzchołków; i++){
						macierzSąsiedztwa[i] = new bool[liczbaWierzchołków];
						for(int j = 0; j < liczbaWierzchołków; j++)
							macierzSąsiedztwa[i][j] = 0;
					}
					GenerateGraphMS(macierzSąsiedztwa, liczbaWierzchołków, liczbaKrawędzi);

				/*	for(int i = 0; i < liczbaWierzchołków; i++){
						for(int j = 0; j < liczbaWierzchołków; j++)
							printf("%d ", macierzSąsiedztwa[i][j]);
						printf("\n");
					}*/

					isCorrectAnswer = true;
					break;
				case 2:// // Graf skierowany
					listaNastępników = new std::list<int>[liczbaWierzchołków];
					GenerateGraphLN(listaNastępników, liczbaWierzchołków, liczbaKrawędzi);
					isCorrectAnswer = true;

					/*for(int i = 0; i < liczbaWierzchołków; i++){
						printf("%d ->: ", i);
						for(std::list<int>::iterator j = listaNastępników[i].begin(); j != listaNastępników[i].end(); j++){
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
			printf("\nCo chcesz zrobić z grafem:\n");
			printf("  1  Znajdź cykl Hamiltona z wykorzystaniem algorytmu Robersta-Floresa;\n");
			printf("  2  Znajdź cykl Eulera z wykorzystaniem algorytmu Fleury'ego;\n");
			printf("  3  Nowy graf;\n");
			printf("  4  Zakończ;\n");

			printf("Give your answer:");
			scanf_s("%d", &answer);

			if(type == 1){// Graf Nieskierowany
				switch(answer){
					case 1://algorytm Robersta-Floresa (cykl Hamiltona)
						start = std::chrono::system_clock::now();
						GNS_Hamilton(macierzSąsiedztwa, liczbaWierzchołków);
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(GNS Hamilton): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 2://algorytm Fleury'ego (cykl Eulera)
						start = std::chrono::system_clock::now();
						if(IsEulerianMS(macierzSąsiedztwa, liczbaWierzchołków)){
							GNS_Euler(macierzSąsiedztwa, liczbaWierzchołków);
						} else{//nie posiada cyklu
							printf("Graf nie posiada cyklu Eulera\n");
						}
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(GNS Euler): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 3:
						isCorrectAnswer = true;
						for(int i = 0; i < liczbaWierzchołków; ++i)
							delete[] macierzSąsiedztwa[i];
						delete[] macierzSąsiedztwa;
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
						GS_Hamilton(listaNastępników, liczbaWierzchołków);
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(GS Hamilton): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 2://algorytm Fleury'ego (cykl Eulera)
						start = std::chrono::system_clock::now();
						if(IsEulerianLN(listaNastępników, liczbaWierzchołków)){
							GS_Euler(listaNastępników, liczbaWierzchołków);	
						} else{//nie posiada cyklu
							printf("Graf nie posiada cyklu Eulera");
						}
						end = std::chrono::system_clock::now();
						std::cout << "\nTime in microseconds(GS Euler): " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
						break;
					case 3:
						isCorrectAnswer = true;
						delete[] listaNastępników;
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

