#pragma once

class cell {
private:
	int size;

public:
	int x, y;
	bool state;

	cell();
	void draw();
};
