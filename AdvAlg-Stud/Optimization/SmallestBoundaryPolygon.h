#pragma once
#include <vector>
#include "../Utils/Animlog.h"

// Adot ponthalmazt legkisebb k�rbe fogo polygon probl�ma 
// Van sok pont �s meg kell hat�rozni azt a polygont aminek ker�lete a legkisebb

const float PI = 3.14159265358979f;

class Point
{
public:
	float x;
	float y;
};

class SmallestBoundaryPolygonProblem
{
protected:
	std::vector<Point> points;

	float distanceFromLine(Point lp1, Point lp2, Point p);
	float outerDistanceToBoundary(std::vector<Point> solution);
	float lengthOfBoundary(std::vector<Point> solution);

	float objective(std::vector<Point> solution);
	float constraint(std::vector<Point> solution);
public:
	SmallestBoundaryPolygonProblem();
	void loadPointsFromFile(std::string fileName);
	void savePointsToFile(std::string fileName, std::vector<Point> pointVector);
	void printOutPoints(std::vector<Point> pointVector);
};