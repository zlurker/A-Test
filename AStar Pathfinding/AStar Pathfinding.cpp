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

	bool used;
	int hCost;
	int gCost;
	int fCost;
	int pointId;

	point() {
		upNeighbour = -1;
		downNeighbour = -1;
		leftNeighbour = -1;
		rightNeighbour = -1;

		hCost = -1;
		gCost = -1;
		fCost = 0;

		used = false;
	}
};


class pointwrapper {
public:
	pointwrapper(point* ptr) {
		pointer = ptr;
		fCostVal = ptr->fCost;
		cout << "Adding cost: " << fCostVal << " (" << ptr->pointId << ")" << endl;
	}

	point* pointer;
	int fCostVal;
};

struct orderPointValue
{
	bool operator() (pointwrapper const a, pointwrapper const b) { return a.fCostVal > b.fCostVal; }
};

priority_queue <pointwrapper, vector<pointwrapper>, orderPointValue> nextPoint;
unordered_map<int, point*> map;

bool retCoords(int id, int* arr) {
	if (id < 0 || id >= x*y)
		return false;

	arr[1] = id % x;
	arr[0] = (id - arr[1]) / x;
	return true;
}

void calculateCost(int id, int gCost) {
	if (id < 0 || id >= x*y)
		return;

	if (map[id]->hCost == -1) {

		int coords0[2];
		int coords1[2];

		retCoords(id, coords0);
		retCoords(endNode, coords1);

		int xDiff, yDiff = 0;

		xDiff = abs(coords1[1] - coords0[1]);
		yDiff = abs(coords1[0] - coords0[0]);

		map[id]->hCost = (xDiff * xDiff) + (yDiff * yDiff);
	}

	if (map[id]->gCost == -1 || map[id]->gCost > gCost && !map[id]->used) {
		map[id]->gCost = gCost;
		map[id]->fCost = gCost + map[id]->hCost;
	}

	nextPoint.push(pointwrapper(map[id]));
}

int main()
{
	int pointData[y][x] = {
		{ 0,0,0,0,0,0,0,0,0,2 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,3,3,3,3,3,3,3,3,3 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,1,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 }
	};

	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++) {
			int idVal = (i*x) + j;

			switch (pointData[i][j]) {
			case 1:
				startNode = idVal;
				cout << "Start: " << startNode << endl;
				break;
			case 2:
				endNode = idVal;
				cout << "End: " << endNode << endl;
				break;

			case 3:
				continue;
			}

			point* p = new point();

			p->pointId = idVal;
			map.insert(pair<int, point*>(idVal, p));

			int leftCell = idVal - 10;
			int downCell = idVal - 1;

			if (map.count(leftCell) == 1) {
				map[leftCell]->rightNeighbour = idVal;
				p->leftNeighbour = leftCell;
				//cout << "Transaction horizontal with " << idVal << " and " << leftCell << endl;
			}

			if (map.count(downCell) == 1) {
				map[downCell]->upNeighbour = idVal;
				p->downNeighbour = downCell;
				//cout << "Transaction vertical with " << idVal << " and " << downCell << endl;
			}
		}

	if (startNode == -1 || endNode == -1) {
		cout << "sN or eN has not been set! Ending process...";
		system("pause");
		return 0;
	}

	map[startNode]->fCost = 0;
	map[startNode]->gCost = 0;
	map[startNode]->hCost = 0;
	map[startNode]->used = true;
	nextPoint.push(pointwrapper(map[startNode]));

	cout << "Begin path searching...";

	while (!nextPoint.empty()) {
		point* pInst;
		bool updated = false;

		while (!updated) {
			if (nextPoint.empty())
				break;

			pointwrapper pw = nextPoint.top();
			pInst = pw.pointer;

			cout << "Retrieved Cost: " << pw.fCostVal << "Actual Cost: " << pInst->fCost << endl;

			if (pInst->fCost == pw.fCostVal)
				updated = true;

			nextPoint.pop();
		}

		if (pInst == nullptr)
			break;

		pInst->used = true;

		for (int i = 0; i < x*y; i++) {
			//cout << "bool result: " << map[i].used << endl;
			if (i == startNode)
				cout << "S ";
			else if (i == endNode)
				cout << "E ";
			else if (map.count(i) == 0)
				cout << "B ";
			else if (map[i]->used)
				cout << "* ";
			else
				cout << map[i]->fCost << " ";

			if ((i + 1) % x == 0)
				cout << endl;
		}

		if (pInst->downNeighbour == endNode || pInst->upNeighbour == endNode || pInst->leftNeighbour == endNode || pInst->rightNeighbour == endNode) {
			cout << "Path has been found!";
			system("pause");
			return 0;
		}

		system("pause");
		system("CLS");

		//
		//cout << "change result: " << pInst->used << endl;
		int newGCost = pInst->gCost + 1;

		calculateCost(pInst->leftNeighbour, newGCost);
		calculateCost(pInst->rightNeighbour, newGCost);
		calculateCost(pInst->upNeighbour, newGCost);
		calculateCost(pInst->downNeighbour, newGCost);



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

	cout << "Path has not been found!";
	system("pause");

	return 0;
}

