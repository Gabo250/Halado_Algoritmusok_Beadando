#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include "TravellingSalesman.h"
#include "../Utils/Animlog.h"
#include "../Utils/Random.h"

using namespace std;

TravellingSalesmanProblem::TravellingSalesmanProblem() {
}

float TravellingSalesmanProblem::objective(vector<Town> solution) {
	float sum_length = 0;

	for (unsigned int ti = 0; ti < solution.size() - 1; ti++) {
		Town t1 = solution[ti];
		Town t2 = solution[ti + 1];
		sum_length += sqrt(pow(t1.x - t2.x, 2) + pow(t1.y - t2.y, 2));
	}
	return sum_length;
}

void TravellingSalesmanProblem::loadTownsFromFile(string fileName) {
	ifstream ftowns(fileName);
	while (!ftowns.eof()) {
		Town town;
		ftowns >> town.x;
		ftowns >> town.y;
		towns.push_back(town);
	};
	ftowns.close();

	cout << "Loaded towns:" << endl;
	printOutTowns(towns);
	cout << "\n" << objective(towns);
}

void TravellingSalesmanProblem::saveTownsToFile(string fileName, vector<Town> townVector) {
	ofstream ftowns(fileName, ios_base::app);
	for (Town twn : townVector) {
		ftowns << twn.x << "\t" << twn.y << endl;
	};
	ftowns.close();
}

void TravellingSalesmanProblem::printOutTowns(vector<Town> townVector) {
	for (Town twn : townVector) {
		cout << "(" << twn.x << "," << twn.y << ")" << endl;
	}
}

