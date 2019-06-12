#pragma once
#include <vector>
#include "../Utils/Animlog.h"
#include "../Utils/Random.h"
#include "SmallestBoundaryPolygon.h"

// Legkisebb körbefoglaló polygon megoldása Hegymászó algoritmussal

using namespace std;

class SmallestBoundarySolver : public SmallestBoundaryPolygonProblem
{
protected:
	vector<Point> BoundaryPoints;
	int PointNumber;
	string Filename;
	void HillClimbingStochastic(float epsilon);
	Point CenterPointofCircle();
	float RadiusofCircle();
public:
	SmallestBoundarySolver(int PointNumber, string FileName);
	void GenerateRandomPointsOnaCircle();	
	virtual void Optimalize(int iterration, float epsilon);
};
