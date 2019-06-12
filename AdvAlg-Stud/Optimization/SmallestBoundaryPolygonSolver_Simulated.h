#pragma once
#include <vector>
#include "../Utils/Animlog.h"
#include "../Utils/Random.h"
#include "SmallestBoundaryPolygon.h"
#include "SmallestBoundaryPolygonSolver.h"

// Legkisebb körbefoglaló polygon megoldása szimulált lehûlés elvû hegymászó algoritmussal

const float e = 2.71828182846;

class SmallestBoundarySolver_Simulated : public SmallestBoundarySolver
{
	void Initalize();
	float Temperature(float Tmax, float T);
	void Simulated(float epsilon, int Kb);
public:
	SmallestBoundarySolver_Simulated(string filename, int pointnumber) : SmallestBoundarySolver(pointnumber, filename) {};
	void Optimalize(int iterration, float epsilon) override;
};