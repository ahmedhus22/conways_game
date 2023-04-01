#pragma once

class cell {
private:
	int size;

public:
	int x, y;
	bool state;
	int no_of_neighbours;
	cell();
	void draw();
};
