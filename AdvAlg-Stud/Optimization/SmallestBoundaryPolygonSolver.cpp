#include <vector>
#include "stdafx.h"
#include "../Utils/Animlog.h"
#include "../Utils/Random.h"
#include "SmallestBoundaryPolygon.h"
#include "SmallestBoundaryPolygonSolver.h"
#include <math.h>

using namespace std;

SmallestBoundarySolver::SmallestBoundarySolver(int PointNumber, string Filename)
{
	this->PointNumber = PointNumber;
	this->Filename = Filename;
}

Point SmallestBoundarySolver::CenterPointofCircle()
{
	float Sumx = 0;
	float Sumy = 0;
	Point center;
	for (Point p : points)
	{
		Sumx += p.x;
		Sumy += p.y;
	}

	center.x = Sumx / points.size();
	center.y = Sumy / points.size();
	return center;
}

// generate radius of the circle
float SmallestBoundarySolver::RadiusofCircle()
{
	float MaxDistancefromPoint = 0;
	Point center = CenterPointofCircle();
	for (Point p : points)
	{
		float distance = sqrt(pow(p.x - center.x, 2) + pow(p.y - center.y, 2));
		if (distance > MaxDistancefromPoint)
		{
			MaxDistancefromPoint = distance;
		}
	}

	return MaxDistancefromPoint * 2.2;
}

// generate points on the circle
void SmallestBoundarySolver::GenerateRandomPointsOnaCircle()
{
	Point actpoint;
	float degree = 360 / PointNumber;
	float radius = RadiusofCircle();
	Point center = CenterPointofCircle();
	cout << endl << "Circlepoints:" << endl;
	for (int i = 0; i < PointNumber; i++)
	{
		actpoint.x = cos((i * degree) * (PI / 180)) * radius + center.x;
		actpoint.y = sin((i * degree) * (PI / 180)) * radius + center.y;
		BoundaryPoints.push_back(actpoint);
	}

	savePointsToFile(Filename, BoundaryPoints);
	for (Point p : BoundaryPoints)
	{
		cout << "(" << p.x << "," << p.y << ")" << endl;
	}
}

// HillClimbing Algorithm
void SmallestBoundarySolver::HillClimbingStochastic(float epsilon)
{
	int r = randomUniform(0, PointNumber - 1);
	Point p = BoundaryPoints.at(r);
	vector<Point> cpy = BoundaryPoints;
	int i = 0;
	while (i < 1000)
	{
		float x = randomUniform(-epsilon, epsilon);
		float y = randomUniform(-epsilon, epsilon);
		p.x += x;
		p.y += y;
		cpy.at(r) = p;
		if (constraint(cpy) != -1 && constraint(cpy) < constraint(BoundaryPoints) && objective(cpy) <= objective(BoundaryPoints))
		{
			BoundaryPoints = cpy;
			savePointsToFile(Filename, BoundaryPoints);
		}
		else
		{
			p.x -= x;
			p.y -= y;
		}

		i++;
	}
}

// The Algorithm starter
void SmallestBoundarySolver::Optimalize(int iterration, float epsilon)
{
	for (int i = 0; i < iterration; i++)
	{
		HillClimbingStochastic(epsilon);
	}

	cout << endl << "optimalized" << endl;
	for (Point p : BoundaryPoints)
	{
		cout << "(" << p.x << "," << p.y << ")" << endl;
	}

	cout << lengthOfBoundary(BoundaryPoints);
}