#pragma once
#include <vector>
#include "../Utils/Animlog.h"
#include "../Utils/Random.h"
#include "TravellingSalesman.h"

// Utazó ühynök probléma genetikus algoritmussal

using namespace std;

class TravellingSalesmanSolver : public TravellingSalesmanProblem
{
private:	
	vector<vector<Town>> Population;
	string fileName;
	void Initalize();
	void Evaluation(vector<vector<Town>> &p);
	vector<vector<Town>> Selection(int n);
	void SwingerClub(vector<Town> &t1, vector<Town> &t2);
	void Mutate(vector<Town> &t);
	void Drop(vector<vector<Town>> &p);
public:
	TravellingSalesmanSolver(string Name);	
	void GeneticAlgorithm(int iter);
};