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
int startNode, endNode = -1;


class point {
public:
	int upNeighbour;
	int downNeighbour;
	int leftNeighbour;
	int rightNeighbour;

	bool oList;
	bool cList;
	int hCost;
	int gCost;
	int fCost;

	point() {
		upNeighbour = -1;
		downNeighbour = -1;
		leftNeighbour = -1;
		rightNeighbour = -1;
	}
};

struct orderPointValue
{
	bool operator() (point const &a, point const &b) { return a.fCost > b.fCost; }
};

bool retCoords(int id, int* arr) {
	if (id < 0 || id >= x*y)
		return false;

	arr[1] = id % x;
	arr[0] = (id - arr[1]) / x;
	return true;
}

int calculateHCost(int id) {
	if (id < 0 || id >= x*y)
		return;

	int coords0[2];
	int coords1[2];

	retCoords(id, coords0);
	retCoords(endNode, coords1);

	int xDiff, yDiff = 0;

	xDiff = abs(coords1[1] - coords0[1]);
	yDiff = abs(coords1[0] - coords0[0]);

	int hCost = (xDiff * xDiff) + (yDiff * yDiff);

	// returns F which is H + G
	return hCost;
}

int main()
{
	priority_queue <point, vector<point>, orderPointValue> nextPoint;
	unordered_map<int, point> map;

	int pointData[y][x] = {
		{ 0,0,0,0,0,0,0,0,0,2 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,1,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 }
	};



	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++) {
			point p = point();
			int idVal = (i*x) + j;
			int coords[2];

			int leftCell = idVal - 10;
			int downCell = idVal - 1;

			if (leftCell > -1) {
				map[leftCell].rightNeighbour = idVal;
				p.leftNeighbour = leftCell;
				//cout << "Transaction horizontal with " << idVal << " and " << leftCell << endl;
			}

			if (downCell > -1) {
				map[downCell].upNeighbour = idVal;
				p.downNeighbour = downCell;
				//cout << "Transaction vertical with " << idVal << " and " << downCell << endl;
			}

			map.insert(pair<int, point>(idVal, p));

			switch (pointData[i][j]) {
			case 0:
				startNode = idVal;
				break;
			case 1:
				endNode = idVal;
				break;
			}
		}

	if (startNode == -1 || endNode == -1) {
		cout << "sN or eN has not been set! Ending process...";
		system("pause");
		return 0;
	}

	map[startNode].fCost = 0;
	nextPoint.push(map[startNode]);

	while (!nextPoint.empty()) {
		point pInst = nextPoint.top();
		
	}

	//for (int i = 0; i < y; i++)
		//for (int j = 0; j < x; j++)
			//cout << "Test val: " << map[(i*x) + j].pointValue << endl;

	/*point p1 = point();
	p1.pointValue = 5;

	point p2 = point();
	p2.pointValue = 50;

	point p3 = point();
	p3.pointValue = 1;

	nextPoint.push(p1);
	nextPoint.push(p2);
	nextPoint.push(p3);*/

	//while (!nextPoint.empty()) {
		//cout << "P value " << nextPoint.top().totalCost << endl;
		//nextPoint.pop();
	//}

	cout << "Path has been found!";
	system("pause");

	return 0;
}

