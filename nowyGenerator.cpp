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
