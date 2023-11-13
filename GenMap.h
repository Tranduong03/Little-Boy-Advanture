#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "stdrand.h"
#include "Engine.h"
#include "TextureManager.h"

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
	bool isFlag;
};


class Map
{
private:
	pixel** map;
	int cols, rows;
	int Boom;
	static Map* CurrentMap;

public:
	static Map* GetInstance() {
		return CurrentMap = (CurrentMap != nullptr) ? CurrentMap : new Map();
	};
	static Map* GetInstance(int x, int y, int level) {
		CurrentMap = nullptr;
		return CurrentMap = new Map(x, y, level);
	}
	Map();
	Map(int, int, int);
	~Map();

	//void NewMap(int, int, int);
	//void clean();

	void setMap(int);	// level

	int countBoomOnPixel(int, int);	// input: index

	void printMap();	// level

	int getBoom();

	void DrawPixel();

	void UpdateMap(struct position pos, SDL_Event);

	int CheckMap();

	void OpenCellVal0(int, int);

	void MapWinOpen();

	void MapLoseOpen();

	int getRows() { return rows; }

	struct position getcell_locate(int, int);// l?y v? trí ô t? v? trí chu?t

	int score();
};
