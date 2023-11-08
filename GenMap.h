#pragma once

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "stdrand.h"

enum {
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
    SIX,
    SEVEN,
    EIGHT,
    BOOM
};

struct pixel {
	int data;
	bool status;
};

class Map
{
private:
	pixel **map;
	int cols, rows;
	int Boom;
public:
	Map();
	Map(int, int);
	void setMap(int);	// level
	int countBoomOnPixel(int, int);	// input: index
	void printMap(int);	// level
	int getBoom() { return Boom; };
	~Map();
};


