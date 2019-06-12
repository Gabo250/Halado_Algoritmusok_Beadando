#include <vector>
#include "stdafx.h"
#include "../Utils/Animlog.h"
#include "../Utils/Random.h"
#include "SmallestBoundaryPolygon.h"
#include "SmallestBoundaryPolygonSolver.h"
#include "SmallestBoundaryPolygonSolver_Simulated.h"
#include <math.h>

using namespace std;

void SmallestBoundarySolver_Simulated::Initalize()
{
	loadPointsFromFile("Input\\Points.txt");
	GenerateRandomPointsOnaCircle();
}

float SmallestBoundarySolver_Simulated::Temperature(float Tmax, float T)
{
	return Tmax * (1 - (T / Tmax));
}

void SmallestBoundarySolver_Simulated::Simulated(float epsilon, int Kb)
{
	int r = randomUniform(0, PointNumber - 1);
	Point p = BoundaryPoints.at(r);
	vector<Point> cpy = BoundaryPoints;
	int t = 1;
	int i = 0;
	while (i < 20)
	{
		float x = randomUniform(-epsilon, epsilon);
		float y = randomUniform(-epsilon, epsilon);
		p.x += x;
		p.y += y;
		cpy.at(r) = p;
		float energy = objective(cpy) - objective(BoundaryPoints);
		if (constraint(cpy) != -1 && energy < 0)
		{
			BoundaryPoints = cpy;
			savePointsToFile(Filename, BoundaryPoints);
		}
		else if (constraint(cpy) != -1)
		{
			float temp = Temperature(50, t);
			float k = pow(e, -(energy / (Kb * temp)));
			float rand = randomUniform(0.0f, 1.0f);
			if (rand <= k && abs(constraint(cpy) - constraint(BoundaryPoints)) < 1)
			{
				BoundaryPoints = cpy;
				savePointsToFile(Filename, BoundaryPoints);
			}
			else
			{
				p.x -= x;
				p.y -= y;
			}
		}
		else
		{
			p.x -= x;
			p.y -= y;
		}

		i++;
		t++;
	}
}

void SmallestBoundarySolver_Simulated::Optimalize(int iterration, float epsilon)
{
	Initalize();
	for (int i = 0; i < iterration; i++)
	{
		Simulated(epsilon, 5);
	}

	cout << endl << "optimalized" << endl;
	for (Point p : BoundaryPoints)
	{
		cout << "(" << p.x << "," << p.y << ")" << endl;
	}

	cout << lengthOfBoundary(BoundaryPoints);
}