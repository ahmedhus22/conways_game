#pragma once
#include "raylib.h"

class cell {
private:
	int size;

public:
	int x, y;
	bool state;
	int no_of_neighbours;
	cell();
	void draw();
	Rectangle get_cell();
	bool operator==(cell& c) { return (x == c.x && y == c.y); }
	bool operator!=(cell& c) { return !operator==(c); }
};
