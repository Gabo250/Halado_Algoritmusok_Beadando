#include "stdafx.h"
#include <string>
#include "SmallestBoundaryPolygonSolver.h"
#include "SmallestBoundaryPolygon.h"
#include "SmallestBoundaryPolygonSolver_Simulated.h"
#include "TravellingSalesman.h"
#include "TravellingSalesmanSolver.h"

void SmallestBoundaryPolygon_HillClimbingStochastic() 
{
	SmallestBoundarySolver problem(10, "Log\\SmallestBoundaryPolygon_HillClimbingStochastic.txt");
	problem.loadPointsFromFile("Input\\Points.txt");
	problem.GenerateRandomPointsOnaCircle();
	problem.Optimalize(1500, 10.0f);
}

void SmallestBoundaryPolygon_Simulated()
{
	SmallestBoundarySolver_Simulated problem("Log\\SmallestBoundaryPolygon_Simulated.txt", 10);
	problem.Optimalize(1500, 10.0f);
}

void TravellingSalesmanSolv()
{
	TravellingSalesmanSolver problem("Log\\TravellingSalesman.txt");
	problem.loadTownsFromFile("Input\\Towns.txt");
	problem.GeneticAlgorithm(2000);
}

int main()
{
	//SmallestBoundaryPolygon_HillClimbingStochastic();
	//TravellingSalesmanSolv();
	SmallestBoundaryPolygon_Simulated();
	return 0;
}