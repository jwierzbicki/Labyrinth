// POP 2015-12-22 projekt 1 Wierzbicki Jacek EIT
// u¿yte IDE: Dev-C++ 5.6.0
#include "stdafx.h" // for MS Visual Studio
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
///////////////////////////////////////////////////////
// !!! wielkosc labiryntu !!!
const int ROW = 7;
const int COL = 10;
/////////////////////////////////////////////////////
// deklaracje funkcji
void print(char [ROW][COL]);
void option(char [ROW][COL], char [ROW][COL], char&, int&, int&, int&);
void forward(char [ROW][COL], char [ROW][COL], char&, int&, int&, int&);
void left(char [ROW][COL], char [ROW][COL], char&, int&, int&, int&);
void right(char [ROW][COL], char [ROW][COL], char&, int&, int&, int&);
void teleport(char [ROW][COL], char [ROW][COL], char&, int&, int&, int&);


int main()
{
	srand(time(NULL));
	int posx = 5; // !!! kordy poczatkowe !!!
	int posy = 9; // !!! kordy poczatkowe !!!
	char direction = 'W';		// !!! zwrot gracza !!!
	int energy = 750;
	char lab1[ROW][COL] ={{'#','#','#','#','#','#','#','#','#','#'},
					      {' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
					      {'#','#','#',' ','#','#','#','#',' ','#'},
					      {'#',' ','#',' ','#',' ',' ',' ',' ','#'},
					      {'#',' ','#','#','#',' ','#','#','#','#'},
						  {'#',' ',' ',' ',' ',' ',' ',' ',' ',' '},
						  {'#','#','#','#','#','#','#','#','#','#'}};
						  
	char lab2[ROW][COL] ={{'?','?','?','?','?','?','?','?','?','?'},
					      {'?','?','?','?','?','?','?','?','?','?'},
					      {'?','?','?','?','?','?','?','?','?','?'},
					      {'?','?','?','?','?','?','?','?','?','?'},
					      {'?','?','?','?','?','?','?','?','?','?'},
					      {'?','?','?','?','?','?','?','?',' ','<'},
					      {'?','?','?','?','?','?','?','?','?','?'}};

	cout << "Witaj eksploratorze, trafiles do labiryntu, powodzenia.\n\n";
	system("pause");
	do{
        system("cls");
		print(lab2);
		cout << "Co robisz?" << endl;
		cout << "N, aby pojsc prosto" << endl << "L, aby skrecic w lewo" << endl << "P, aby skrecic w prawo" << endl << "T, aby sie teleportowac" << endl;
		cout << "\t\tObecna energia: " << energy << endl;
		option(lab1,lab2,direction,posx,posy,energy);

	}while(lab2[1][0]!='<' && energy>0); // !!! warunek koncowy lab2[x][y] !!!

	if(energy==0) cout << "Energia wyczerpana.\n\n";
	else cout << "Przeszedles labirynt, gratulacje.\n\n";

	system("pause");
	return 0;
}
///////////////////////////////////////////////
// funkcje
void print(char tab[ROW][COL])		//wyswietlanie labiryntu
{
	for(int i=0; i<ROW; i++){
		for(int j=0; j<COL; j++)
		cout << tab[i][j];
		cout << endl;
	}
	cout << endl;
}

void option(char tab1[ROW][COL], char tab2[ROW][COL], char &dir, int &x, int &y, int &E)		//funkcja glowna / wybor opcji
{
    char choice;
	cin >> choice;
	switch(choice){
		case 'N': forward(tab1, tab2, dir, x, y, E); break;
		case 'L': left(tab1, tab2, dir, x, y, E); break;
		case 'P': right(tab1, tab2, dir, x, y, E); break;
		case 'T': teleport(tab1, tab2, dir, x, y, E); break;
	}
}

void forward(char tab1[ROW][COL], char tab2[ROW][COL], char &dir, int &x, int &y, int &E)	//naprzod
{
	if(dir=='N' && tab2[x-1][y]==' ')
		{
		tab2[x][y] = tab1[x][y];
		tab2[x-1][y] = '^';
		tab2[x-2][y] = tab1[x-2][y];
		x-=1;
		E-=15;
		}
	else if(dir=='S' && tab2[x+1][y]==' ')
		{
		tab2[x][y] = tab1[x][y];
		tab2[x+1][y] = 'V';
		tab2[x+2][y] = tab1[x+2][y];
		x+=1;
		E-=15;
		}
	else if(dir=='W' && tab2[x][y-1]==' ')
		{
		tab2[x][y] = tab1[x][y];
		tab2[x][y-1] = '<';
		tab2[x][y-2] = tab1[x][y-2];
		y-=1;
		E-=15;
		}
	else if(dir=='E' && tab2[x][y+1]==' ')
		{
		tab2[x][y] = tab1[x][y];
		tab2[x][y+1] = '>';
		tab2[x][y+2] = tab1[x][y+2];
		y+=1;
		E-=15;
		}
	else{
		cout << "Przed toba sciana\n" << endl;
		system("pause");
		}
}

void left(char tab1[ROW][COL], char tab2[ROW][COL], char &dir, int &x, int &y, int &E)		//obrot w lewo
{
	switch(dir){
		case 'N': 	dir = 'W';
					tab2[x][y] = '<';
					tab2[x][y-1] = tab1[x][y-1];
					break;
		case 'S': 	dir = 'E';
					tab2[x][y] = '>';
					tab2[x][y+1] = tab1[x][y+1];
					break;
		case 'W': 	dir = 'S';
					tab2[x][y] = 'v';
					tab2[x+1][y] = tab1[x+1][y];
					break;
		case 'E': 	dir = 'N';
					tab2[x][y] = '^';
					tab2[x-1][y] = tab1[x-1][y];
					break;
	}
	E-=10;
}

void right(char tab1[ROW][COL], char tab2[ROW][COL], char &dir, int &x, int &y, int &E)		//obrot w prawo
{
	switch(dir){
		case 'N': 	dir = 'E';
					tab2[x][y] = '>';
					tab2[x][y+1] = tab1[x][y+1];
					break;
		case 'S': 	dir = 'W';
					tab2[x][y] = '<';
					tab2[x][y-1] = tab1[x][y-1];
					break;
		case 'W': 	dir = 'N';
					tab2[x][y] = '^';
					tab2[x-1][y] = tab1[x-1][y];
					break;
		case 'E': 	dir = 'S';
					tab2[x][y] = 'v';
					tab2[x+1][y] = tab1[x+1][y];
					break;
	}
	E-=10;
}

void teleport(char tab1[ROW][COL], char tab2[ROW][COL], char &dir, int &x, int &y, int &E)
{
	int rx, ry;
	tab2[x][y] = tab1[x][y];	 // usuniecie obecnej pozycji
	

	rx = rand()%ROW;		// losowanie pozycji
	ry = rand()%COL;		// -//-
	
	if(tab1[rx][ry]!='#' && tab1[rx][ry]!=tab2[1][0] && tab2[rx][ry]!=' '){

		///// losowanie zwrotu
		int rdir = rand()%4;
		switch(rdir){
			case 0: dir = 'N';
					tab2[rx][ry] = '^';
					tab2[rx-1][ry] = tab1[rx-1][ry];
					break;
			case 1: dir = 'S';
					tab2[rx][ry] = 'V';
					tab2[rx+1][ry] = tab1[rx+1][ry];
					break;
			case 2: dir = 'W';
					tab2[rx][ry] = '<';
					tab2[rx][ry-1] = tab1[rx][ry-1];
					break;
			case 3: dir = 'E';
					tab2[rx][ry] = '>';
					tab2[rx][ry+1] = tab1[rx][ry+1];
					break;
			}
		/////
		x = rx;
		y = ry;
		E-=30;
	}else teleport(tab1,tab2,dir,x,y,E);
}

