void GenerateGraphMS(bool **macierz, int v, int e){
	int i, x, y;
	i = 0;
	while(i < e){
		x = rand() % v;
		y = rand() % v;
		if(x != y && !macierz[x][y]){
			macierz[x][y] = 1;
			macierz[y][x] = 1;
			i++;
		}
	}

	//modify to have EULER
	for(int i = 0; i<v - 1; i++){
		//calculate degree
		int deg = 0;
		for(int j = 0; j<v; j++)
			if(macierz[i][j]>0)
				deg++;
		//check if degree is even
		if(deg % 2 != 0){
			int x = rand()%(v - i - 1) + i + 1;
			if(macierz[i][x]>0){
				macierz[i][x] = 0;
				macierz[x][i] = 0;
			} else{
				macierz[i][x] = 1;
				macierz[x][i] = 1;
			}
		}
	}
}


void GenerateGraphLN(std::list<int> *listaNastępników, int v, int e){
	int i, x, y;
	std::list<int>::iterator w;
	i = 0;
	while(i < e){
		x = rand() % v;
		y = rand() % v;
		bool krawędźIstnieje = false;
		for(w = listaNastępników[x].begin(); w != listaNastępników[x].end(); w++){
			if(*w == y){
				krawędźIstnieje = true;
				break;
			}
		}
		if(x != y && !krawędźIstnieje){
			listaNastępników[x].push_back(y);
			i++;
		}
	}

	//modify to have EULER
	int *stopnie = new int[v];
	for(int i = 0; i < v; i++){
		stopnie[i] = listaNastępników[i].size();
	}
	for(int i = 0; i < v; i++){
		for(w = listaNastępników[i].begin(); w != listaNastępników[i].end(); w++){
			stopnie[*w]--;
		}
	}
	for(int i = 0; i<v - 1; i++){
		//calculate degree
		while(stopnie[i] != 0){
			int x = rand() % (v - i - 1) + i + 1;
			if(stopnie[i] > 0){//nadmiar wychodzących
				if(stopnie[x] > 0)
					continue;
				bool krawędźIstnieje = false;//szukamy krawędzi z i do x
				for(w = listaNastępników[i].begin(); w != listaNastępników[i].end(); w++){
					if(*w == x){
						krawędźIstnieje = true;
						break;
					}
				}
				if(krawędźIstnieje){//jeżeli krawędź istnieje - usuwamy
					listaNastępników[i].erase(w);
					stopnie[i]--;
					stopnie[x]++;
				} else{//jeżeli nie istnieje - szukamy odwrotnej
					bool krawędźIstnieje = false;//szukamy krawędzi z x do i
					for(w = listaNastępników[x].begin(); w != listaNastępników[x].end(); w++){
						if(*w == i){
							krawędźIstnieje = true;
							break;
						}
					}
					if(!krawędźIstnieje){//jeżeli nie istnieje - dodajemy ją
						listaNastępników[x].push_back(i);
						stopnie[i]--;
						stopnie[x]++;
					}
				}
			} else{//nadmiar wchodzących
				if(stopnie[x] < 0)
					continue;
				bool krawędźIstnieje = false;//szukamy krawędzi z i do x
				for(w = listaNastępników[i].begin(); w != listaNastępników[i].end(); w++){
					if(*w == x){
						krawędźIstnieje = true;
						break;
					}
				}
				if(!krawędźIstnieje){//jeżeli nie istnieje - dodajemy ją
					listaNastępników[i].push_back(x);
					stopnie[i]++;
					stopnie[x]--;
				} else{//jeżeli istnieje - szukamy odwrotnej
					bool krawędźIstnieje = false;//szukamy krawędzi z x do i
					for(w = listaNastępników[x].begin(); w != listaNastępników[x].end(); w++){
						if(*w == i){
							krawędźIstnieje = true;
							break;
						}
					}if(krawędźIstnieje){//jeżeli krawędź istnieje - usuwamy
						listaNastępników[x].erase(w);
						stopnie[i]++;
						stopnie[x]--;
					}
				}
			}
		}
	}
}
