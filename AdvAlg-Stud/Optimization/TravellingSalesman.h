#pragma once
#include <vector>
#include "../Utils/Animlog.h"

// Utaz� �gyn�k probl�ma
// Van sok v�ros, minden v�rost csak egyszer �rinthet,
// meg kell hat�rozni a legr�videbb utat - minim�lis fesz�t�f�t

class Town
{
public:
	float x;
	float y;
};

class TravellingSalesmanProblem
{
protected:
	std::vector<Town> towns;
	float objective(std::vector<Town> solution);
public:
	TravellingSalesmanProblem();
	void loadTownsFromFile(std::string fileName);
	void saveTownsToFile(std::string fileName, std::vector<Town> townVector);
	void printOutTowns(std::vector<Town> townVector);
};
