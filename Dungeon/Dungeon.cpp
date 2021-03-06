// Dungeon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <math.h>



using namespace std;


int WIDTH;
int HEIGHT;
int TRAPS;
int ENEMIES;
int mode(0);
int lvl(0);
bool has_won(0);


std::vector< std::vector<char> > dun;

void init_array()
{
	dun.resize(HEIGHT);
	for (size_t i = 0; i < HEIGHT; ++i)
		dun[i].resize(WIDTH);
}

void input_vals() {
	cout << "Set the Height: " << '\n';
	cin >> HEIGHT;
	cout << "Set the Width: " << '\n';
	cin >> WIDTH;
	cout << "Set the number of enemies: " << '\n';
	cin >> ENEMIES;
	cout << "Set the number of traps: " << '\n';
	cin >> TRAPS;

}

void set_vals(int lvl)
{
	WIDTH = HEIGHT = 10 + lvl;
	//ENEMIES = ceil(10 + lvl * 1.2);
	ENEMIES = 2;
	TRAPS = ceil(ENEMIES *2.7);

}

void ClearScreen()
{
	system("CLS");
}


int select_mode()
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "Bienvenido a The Dungeon Game, escoja entre los dos modos de juego: " << '\n';
	SetConsoleTextAttribute(hConsole, 14);
	cout << "Modo Reto (2): ";
	SetConsoleTextAttribute(hConsole, 8);
	cout << "La dificultad va subiendo progresivamente, la mazmorra se" << '\n';
	cout << " agranda y aumenta el numero de enemigos y trampas" << '\n';
	cout << "(solo para jugadores expertos)" << '\n';
	SetConsoleTextAttribute(hConsole, 14);
	cout << "Modo Normal (1): ";
	SetConsoleTextAttribute(hConsole, 8);
	cout << "Establezca el numero de trampas, enemigos y tamano" << '\n';
	cout << " al comienzo de la partida" << '\n' << '\n' << '\n';
	cout << "Escriba 0 o 1 para escoger el modo de juego" << '\n';

set_mode_interior:

	int x = _getch();
	int y(0);
	switch (x)
	{
	case '2':
		y = 2;
		return y;
		break;
	case '1':
		y = 1;
		return y;
		break;
	default:
		cout << "null" << '\n';
		goto set_mode_interior;
		break;
	}
}

void fresh()
{
	for (int i(0); i < HEIGHT; i++)
	{
		for (int j(0); j < WIDTH; j++)
		{
			dun[i][j] = char(250);
		}

	}



}

void f5()
{
	ClearScreen();
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 8);
	cout << "Level: " << lvl;
	cout << '\n' << '\n' << '\n';
	cout << '\t' << '\t';
	SetConsoleTextAttribute(hConsole, 142);
	cout << "|THE DUNGEON GAME|" ;
	SetConsoleTextAttribute(hConsole, 8);
	cout << '\n' << '\n';
	SetConsoleTextAttribute(hConsole, 8);
	cout << '\t' << '\t' << "Move the player ";
	SetConsoleTextAttribute(hConsole, 2);
	cout << "P ";
	SetConsoleTextAttribute(hConsole, 8);
	cout << "with W A S D " << '\n';
	cout << '\t' << '\t' << "Find the treasure ";
	SetConsoleTextAttribute(hConsole, 142);
	cout << "X" << '\n';
	SetConsoleTextAttribute(hConsole, 8);
	cout << '\t' << '\t' << "Don't get hit by enemies ";
	SetConsoleTextAttribute(hConsole, 4);
	cout << "E ";
	SetConsoleTextAttribute(hConsole, 8);
	cout << "or traps ";
	SetConsoleTextAttribute(hConsole, 240);
	cout << "T";
	SetConsoleTextAttribute(hConsole, 8);
	cout << '\n' << '\n' << '\n';



	for (int i(0); i < HEIGHT; i++)
	{
		cout << '\t' << '\t';
		for (int j(0); j < WIDTH; j++)
		{
			switch (dun[i][j])
			{
			case 'P':
			{
				SetConsoleTextAttribute(hConsole, 2);
				cout << dun[i][j];
				break;
			}
			case 'T':
			{
				SetConsoleTextAttribute(hConsole, 240);
				cout << dun[i][j];
				break;
			}
			case 'X':
			{
				SetConsoleTextAttribute(hConsole, 142);
				cout << dun[i][j];
				break;
			}

			case 'E':
			{
				SetConsoleTextAttribute(hConsole, 4);
				cout << dun[i][j];
				break;
			}

			default:
			{
				SetConsoleTextAttribute(hConsole, 8);
				cout << dun[i][j];
				break;
			}
			}
			if (j == WIDTH - 1)
			{
				SetConsoleTextAttribute(hConsole, 8);
				cout << '\n';
			}
		}

	}

}

int rng(int min, int max)
{
	std::random_device seeder;
	std::mt19937 engine(seeder());
	std::uniform_int_distribution<int> dist(min, max);
	int compGuess = dist(engine);
	return compGuess;
}

void gen()
{
	dun[rng(0, HEIGHT-1)][rng(0, HEIGHT-1)] = 'P';

	for (int i(0); i < TRAPS; i++)
	{
		int x;
		int y;

		do
		{
			x = rng(0, HEIGHT-1);
			y = rng(0, HEIGHT-1);
		} while (dun[x][y] != char(250));
			dun[x][y] = 'T';
	}

	for (int i(0); i < ENEMIES; i++)
	{
		int x;
		int y;

		do
		{
			x = rng(0, HEIGHT-1);
			y = rng(0, HEIGHT-1);
		} while (dun[x][y] != char(250));
		dun[x][y] = 'E';
	}

	int x;
	int y;

	do
	{
		x = rng(0, HEIGHT-1);
		y = rng(0, HEIGHT-1);
	} while (dun[x][y] != char(250));
	dun[x][y] = 'X';

	
}

int count(char c)
{
	int x(0);
	for (int i(0); i < HEIGHT; i++)
	{
		for (int j(0); j < WIDTH; j++)
		{
			if (dun[i][j] == c)
				x++;
		}



	}
	return x;
}

bool is_char(char c)
{
	int x(0);
	for (int i(0); i < HEIGHT; i++)
	{
		for (int j(0); j < WIDTH; j++)
		{
			if (dun[i][j] == c)
				x = i;
		}
		
	}
	if (x != 0)
		return true;
	else
		return false;
}

int win_condition()
{

/*
w = 0 ---> jugador muerto
w = 1 ----> victoria
w = 2 ----> sigue el juego

*/

	int p = count('P');
	int x = count('X');
	if (p == 0)
		return 0;
	else if (x == 0)
		return  1;
	else
	return  2;

}

void move_player()
{
	int P_pos[2];
	P_pos[1] = 10000;

	for (int i(0); i < HEIGHT; i++)
	{
		for (int j(0); j < WIDTH && (P_pos[1] == 10000); j++)
		{
			if (dun[i][j] == 'P')
			{
				P_pos[0] = i;
				P_pos[1] = j;
			}
		}
	}

	dun[P_pos[0]][P_pos[1]] = char(250);
	
retry_2:
	switch (_getch()) {
	case 'w':
		if (P_pos[0] == 0)
			dun[HEIGHT - 1][P_pos[1]] = 'P';
		else
			dun[P_pos[0] - 1][P_pos[1]] = 'P';

		break;
	case 's':
		if (P_pos[0] == HEIGHT - 1)
			dun[0][P_pos[1]] = 'P';
		else
			dun[P_pos[0] + 1][P_pos[1]] = 'P';

		break;
	case 'a':
		if (P_pos[1] == 0)
			dun[P_pos[0]][WIDTH - 1] = 'P';
		else
			dun[P_pos[0]][P_pos[1] - 1] = 'P';

		break;
	case 'd':
		if (P_pos[1] == WIDTH - 1)
			dun[P_pos[0]][0] = 'P';
		else
			dun[P_pos[0]][P_pos[1] + 1] = 'P';

		break;
	default:
		cout << endl << "null" << endl;
		goto retry_2;// not arrow
		break;
	}
	int e = count('E');
	int t = count('T');
	int x = count('X');
	if (t != TRAPS)
	{
		cout << '\n' << '\n' << "Has perdido por comerte una trampa " << '\n';
		std::system("PAUSE");
		exit(0);
	}
	else if (e != ENEMIES)
	{
		cout << '\n' << '\n' << "Has perdido por comerte un enemigo " << '\n';
		std::system("PAUSE");
		exit(0);
	}
	else if (x == 0)
	{
		switch (mode)
		{
		case 1:
		{
			cout << '\n' << '\n' << "Has encontrado el tesoro!!" << '\n';
			std::system("PAUSE");
			exit(0); 
			break;
		}
		case 2:
		{
			has_won = 1;
			break;
		}
		
		}
	}
}

void move_IA()
{
	
	vector< vector<int> > P_pos(ENEMIES, vector<int>(2));


	for (int f(0); f < ENEMIES; f++)
	{

		for (int i(0); i < HEIGHT; i++)
		{
			for (int j(0); j < WIDTH; j++)
			{
				if (dun[i][j] == 'E')
				{
					P_pos[f][0] = i;
					P_pos[f][1] = j;
					dun[i][j] = char(250);
					i = HEIGHT + 1;
					j = WIDTH + 1;

				}
			}
		}
	}

	
	for (int f(0); f < ENEMIES; f++)

	{

		int T = TRAPS;
		int X = 1;
		int t(0);
		int x(0);
		int e(0);

	retry:

		int ch = rng(0, 3);
		switch (ch) {
		case 0:
			if (P_pos[f][0] == 0)
			{
				e = count('E');
				dun[HEIGHT - 1][P_pos[f][1]] = 'E';
				t = count('T');
				x = count('X');
				if (t != T)
				{
					dun[HEIGHT - 1][P_pos[f][1]] = 'T';
					goto retry;
				}
				else if (X != x)
				{
					dun[HEIGHT - 1][P_pos[f][1]] = 'X';
					goto retry;
				}
				else if (count('E')!= e+1)
				{
					dun[HEIGHT - 1][P_pos[f][1]] = 'E';
					goto retry;
				}
			}
			else {
				e = count('E');
				dun[P_pos[f][0] - 1][P_pos[f][1]] = 'E';
				t = count('T');
				x = count('X');
				if (t != T)
				{
					dun[P_pos[f][0] - 1][P_pos[f][1]] = 'T';
					goto retry;
				}
				else if (X != x)
				{
					dun[P_pos[f][0] - 1][P_pos[f][1]] = 'X';
					goto retry;
				}
				else if (count('E')!= e+1)
				{
					dun[P_pos[f][0] - 1][P_pos[f][1]] = 'E';
					goto retry;
				}
			}

				break;
		case 1:
			if (P_pos[f][0] == HEIGHT - 1)
			{
				e = count('E');
				dun[0][P_pos[f][1]] = 'E';
				t = count('T');
				x = count('X');
				if (t != T)
				{
					dun[0][P_pos[f][1]] = 'T';
					goto retry;
				}
				else if (X != x)
				{
					dun[0][P_pos[f][1]] = 'X';
					goto retry;
				}
				else if (count('E')!= e+1)
				{
					dun[0][P_pos[f][1]] = 'E';
					goto retry;
				}


			}

			else {
				e = count('E');
				dun[P_pos[f][0] + 1][P_pos[f][1]] = 'E';
				t = count('T');
				x = count('X');
				if (t != T)
				{
					dun[P_pos[f][0] + 1][P_pos[f][1]] = 'T';
					goto retry;
				}
				else if (X != x)
				{
					dun[P_pos[f][0] + 1][P_pos[f][1]] = 'X';
					goto retry;
				}
				else if (count('E')!= e+1)
				{
					dun[P_pos[f][0] + 1][P_pos[f][1]] = 'E';
					goto retry;
				}
			}



			break;
		case 2:
			if (P_pos[f][1] == 0)

			{
				e = count('E');
				dun[P_pos[f][0]][WIDTH - 1] = 'E';
				t = count('T');
				x = count('X');
				if (t != T)
				{
					dun[P_pos[f][0]][WIDTH - 1] = 'T';
					goto retry;
				}
				else if (X != x)
				{
					dun[P_pos[f][0]][WIDTH - 1] = 'X';
					goto retry;
				}
				else if (count('E')!= e+1)
				{
					dun[P_pos[f][0]][WIDTH - 1] = 'E';
					goto retry;
				}

			}
			else
			{
				e = count('E');
				dun[P_pos[f][0]][P_pos[f][1] - 1] = 'E';
				t = count('T');
				x = count('X');
				if (t != T)
				{
					dun[P_pos[f][0]][P_pos[f][1] - 1] = 'T';
					goto retry;
				}
				else if (X != x) {
					dun[P_pos[f][0]][P_pos[f][1] - 1] = 'X';
					goto retry;
				}
				else if (count('E')!= e+1)
				{
					dun[P_pos[f][0]][P_pos[f][1] - 1] = 'E';
					goto retry;
				}
			}
			break;

		case 3:
			if (P_pos[f][1] == WIDTH - 1)
			{
				e = count('E');
				dun[P_pos[f][0]][0] = 'E';
				t = count('T');
				x = count('X');
				if (t != T)
				{
					dun[P_pos[f][0]][0] = 'T';
					goto retry;
				}
				else if (X != x)
				{
					dun[P_pos[f][0]][0] = 'X';
					goto retry;
				}
				else if (count('E')!= e+1)
				{
					dun[P_pos[f][0]][0] = 'E';
					goto retry;
				}

			}
			else {
				e = count('E');
				dun[P_pos[f][0]][P_pos[f][1] + 1] = 'E';
				t = count('T');
				x = count('X');
				if (t != T)
				{
					dun[P_pos[f][0]][P_pos[f][1] + 1] = 'T';
					goto retry;
				}
				else if (X != x) {
					dun[P_pos[f][0]][P_pos[f][1] + 1] = 'X';
					goto retry;
				}
				else if (count('E')!= e+1)
				{
					dun[P_pos[f][0]][P_pos[f][1] + 1] = 'E';
					goto retry;
				}
			}

			break;
		default:
			cout << endl << "null" << endl;  // not arrow
			break;
			}
		}
	}






int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, 600, 600, TRUE);
	mode = select_mode();

	switch (mode)
	{
	case 1:
	{
		input_vals();
		init_array();
		fresh();
		gen();
		do
		{
			f5();
			move_player();
			move_IA();
			if (win_condition() == 0)
			{
				cout << '\n' << '\n' << "Has perdido porque te ha comido un bicho!" << '\n';
				system("PAUSE");
				exit(0);
			}
					
		} while (1);
		return 0;
	}

	case 2:
	{
		while (1)
		{
			has_won = 0;
			set_vals(lvl);
			init_array();
			fresh();
			gen();
			do //Bucle b�sico que encierra al juego
			{
				f5();
				move_player();
				move_IA();
				if (win_condition() == 0)
				{
					cout << '\n' << '\n' << "Has perdido porque te ha comido un bicho!" << '\n';
					system("PAUSE");
					exit(0);
				}

			} while (!has_won);
			lvl++;
		}
			return 0;
		
	}
	
	}
	
}