#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <time.h>

using namespace std;

int* path;
double** matrix, ** pheromone_tab2;
bool* visited2;
double dist2 = 0;




int Probability_ACO(int v, int vnumber)
{
	int i, next, counter=0, numbers, random_number;
	double distance, alfa=1, beta=1, probability, licznik, mianownik=0, probability_tab[100];

	//liczymy mianownik
	for (i = 0; i < vnumber; i++)
	{
		if (visited[i] == 0)
		{
			distance = 1 / matrix[v][i];
			mianownik += pow(pheromone_tab[v][i], alfa) * pow(distance, beta);
		}
	}

	//liczymy prawdopodobienstwa
	for (i = 0; i < vnumber; i++)
	{
		if (visited[i] == 0)
		{
			//jak ze wzoru
			licznik = pow(pheromone_tab[v][i], alfa) * pow(distance, beta);
			probability = licznik / mianownik;
			numbers = probability * 100;

			while (counter < numbers)
			{
				probability_tab[counter++] = i;
			}
		}
	}
	//losowanko ale nie wiem czy dobrze odmierzylem zeby robilo akurat 100 miejsc - do zweryfikowania
	random_number = rand() % 100;
	return probability_tab[random_number];
}


void Pheromone_ACO(int vnumber, int dist)
{
	int i;
	double reduction = 0.7, pheromone_change;
	for (i = 0; i <= vnumber; i++)
	{
		//jak ze wzoru
		if(i != vnumber)
		{
			pheromone_tab[path[i]][path[i + 1]] = reduction * pheromone_tab[path[i]][path[i + 1]] + (dist / 100);
			pheromone_tab[path[i + 1]][path[i]] = reduction * pheromone_tab[path[i+1]][path[i]] + (dist / 100);
		}
		else
		{

			//tutaj laczymy ostatni z pierwszym ale nie wiem czy to dobrze
			pheromone_tab[path[i]][path[0]] = reduction * pheromone_tab[path[i]][path[0]] + (dist / 100);
			pheromone_tab[path[0]][path[i]] = reduction * pheromone_tab[path[0]][path[i]] + (dist / 100);
		}
	}
}

void find_path_ACO(int v, int vnumber, int counter)
{
	int i, j, next;
	visited[v] = 1;
	path[counter++] = v;

	//next = (funkcja na wybor nastepnego wierzcholka - prawdopodobienstwo)
	next = Probability_ACO(v, vnumber);

	if (counter < vnumber) 
	{
		dist += matrix[v][next];
		find_path_ACO(i, vnumber, counter);
	}
	else
		return;
}


int* TSP_ACO(int vnumber)
{
	int j, i, v;

	matrix2 = new double*[vnumber];

	//tablica odwiedzonych
	visited2 = new bool[vnumber];

	//tablica sciezki
	path2 = new int[vnumber];
	//tablica z feromonami
	pheromone_tab = new double *[vnumber];
	for (i = 0; i < vnumber; i++)
	{
		//inicjalizujemy tablice feromonow i ustawiamy ich wartosi poczatkowe na 0
		pheromone_tab[i] = new double[vnumber];
		matrix2[i][j] = new double[vnumber];
		for (j = 0; j < vnumber; j++)
		{
			pheromone_tab[i][j] = 50;
		}
	}
	//robimy to dla kilku mrowek, stad petla
	for (j = 0; j < 10; j++)
	{
		v = rand() % vnumber - 1;
		find_path_ACO(v, vnumber, 0);
		dist += matrix[v][path2[vnumber - 1]];

		//(funcja na dodanie feromonow na podstawie path)
		Pheromone_ACO(vnumber, dist2);

		for (i = 0; i < vnumber; i++)
			visited[j] = 0;
	}

	for (j = 0; j < vnumber; j++)
	{
		cout << path[j] + 1 << " ";
	}
	cout << path[0] + 1 << endl;
}