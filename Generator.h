#pragma once
#include <list>

void GenerateGraphMS(bool **macierz, int n, int e);
void GenerateGraphLN(std::list<int> *listaNastępników, int n, int e);

bool IsEulerianMS(bool **macierz, int n);
bool IsEulerianLN(std::list<int> *lista, int n);
