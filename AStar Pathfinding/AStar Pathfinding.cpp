// AStar Pathfinding.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <queue>
#include <iostream>
#include <functional>
#include <tuple>
#include <unordered_map>
using namespace std;


const int x = 10;
const int y = 10;

class point {
public:
	int upNeighbour;
	int downNeighbour;
	int leftNeighbour;
	int rightNeighbour;
	float pointValue;
};

struct orderPointValue
{
	bool operator() (point const &a, point const &b) { return a.pointValue > b.pointValue; }
};

bool retCoords(int id, int* arr) {
	if (id < 0 || id >= x*y)
		return false;

	arr[1] = id % x;
	arr[0] = (id - arr[1]) / x;
	return true;
}


int main()
{
	priority_queue <point, vector<point>, orderPointValue> nextPoint;
	unordered_map<int, point> map;
	
	float pointData[y][x] = {
		{ 0,0,0,0,0,0,0,0,0,2 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 1,0,0,0,0,0,0,0,0,0 }
	};

	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++) {
			point p = point();
			int idVal = (i*x) + j;
			int coords[2];
			if (retCoords(idVal, coords)) {
				cout << "X: " << coords[1] << "Y: " << coords[0] << endl;
			}
			map.insert(pair<int, point>(idVal, p));		
		}

	//for (int i = 0; i < y; i++)
		//for (int j = 0; j < x; j++)
			//cout << "Test val: " << map[(i*x) + j].pointValue << endl;

	point p1 = point();
	p1.pointValue = 5;

	point p2 = point();
	p2.pointValue = 50;

	point p3 = point();
	p3.pointValue = 1;

	nextPoint.push(p1);
	nextPoint.push(p2);
	nextPoint.push(p3);

	while (!nextPoint.empty()) {
		cout << "P value " << nextPoint.top().pointValue << endl;
		nextPoint.pop();
	}

	system("pause");

	return 0;
}

