#include <vector>
#include "stdafx.h"
#include "../Utils/Animlog.h"
#include "../Utils/Random.h"
#include "TravellingSalesman.h"
#include "TravellingSalesmanSolver.h"
#include <math.h>

using namespace std;

TravellingSalesmanSolver::TravellingSalesmanSolver(string Name)
{	
	fileName = Name;
}

void TravellingSalesmanSolver::Initalize()
{	
	
	for (int i = 0; i < 100; i++)
	{
		vector<Town> s = towns;	
		vector<Town> n;
		for (Town t : s)
		{
			int r = randomUniform(0, s.size() - 1);
			n.push_back(s.at(r));
			s.erase(s.begin() + r);		
		}

		Population.push_back(n);
	}	
}

void TravellingSalesmanSolver::Drop(vector<vector<Town>> &p)
{
	for (int i = p.size() - 1; i > p.size() - 31; i--)
	{
		p.erase(p.begin() + i);
	}
}

void TravellingSalesmanSolver::Evaluation(vector<vector<Town>> &p)
{
	vector<float> f;
	for (vector<Town> v : p)
	{
		f.push_back(objective(v));
	}

	for (int i = 0; i < p.size() - 1; i++)
	{
		for (int j = i + 1; j < p.size(); j++)
		{
			if (f.at(i) > f.at(j))
			{
				float c = f.at(i);
				f.at(i) = f.at(j);
				f.at(j) = c;
				vector<Town> cc = p.at(i);
				p.at(i) = p.at(j);
				p.at(j) = cc;
			}
		}		
	}	
}

vector<vector<Town>> TravellingSalesmanSolver::Selection(int n)
{
	vector<vector<Town>> e;
	for (int i = 0; i < n; i++)
	{
		e.push_back(Population.at(i));
	}

	return e;
}

void TravellingSalesmanSolver::SwingerClub(vector<Town> &t1, vector<Town> &t2)
{
	int m = t1.size() / 4;
	for (int i = 0; i < m; i++)
	{
		int r = randomUniform(0, t1.size() - 1);		
		Town t = t1.at(r);
		Town tt = t2.at(r);
		int m1 = 0;
		int m2 = 0;
		for (int j = 0; j < t1.size(); j++)
		{
			if (tt.x == t1.at(j).x && tt.y == t1.at(j).y)
			{
				m1 = j;
			}

			if (t.x == t2.at(j).x && t.y == t2.at(j).y)
			{
				m2 = j;
			}
		}

		t1.at(r) = tt;
		t2.at(r) = t;		
		Town c = t1.at(m1);
		t1.at(m1) = t2.at(m2);
		t2.at(m2) = c;
	}
}

void TravellingSalesmanSolver::Mutate(vector<Town> &t)
{
	int from = randomUniform(0, (int)(t.size() / 2) - (t.size() / 5));
	int to = randomUniform((int)(t.size() / 2), t.size() - (t.size() / 5));	
	for (int i = 0; i < (t.size() / 5) - 1; i++)
	{
		Town w = t.at(from + i);
		t.at(from + i) = t.at(to + i);
		t.at(to + i) = w;
	}
}

void TravellingSalesmanSolver::GeneticAlgorithm(int iter)
{
	Initalize();
	Evaluation(Population);
	vector<Town> pbest = Population.at(0);
	int i = 0;
	while (i < iter)
	{
		vector<vector<Town>> pnext = Selection(30);
		vector<Town> cpy = pbest;
		for (int k = 0; k < 30; k += 2)
		{
			SwingerClub(pnext.at(k), pnext.at(k + 1));
		}

		for (vector<Town> l : pnext)
		{
			Mutate(l);
			Population.push_back(l);
		}

		Evaluation(Population);
		pbest = Population.at(0);
		i++;
		Drop(Population);		
		saveTownsToFile(fileName, pbest);
	}

	for (Town t : pbest)
	{
		cout << "\n(" << t.x << "," << t.y << ")";
	}

	cout << "\n" << objective(pbest);
}