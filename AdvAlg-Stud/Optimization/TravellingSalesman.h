#pragma once
#include <vector>
#include "../Utils/Animlog.h"

// Utazó ügynök probléma
// Van sok város, minden várost csak egyszer érinthet,
// meg kell határozni a legrövidebb utat - minimális feszítõfát

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
