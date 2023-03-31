#include "cell.h"
#include "raylib.h"

cell::cell() : size(10), state(false), x(0), y(0) {};

void cell::draw() {
	DrawRectangle(x, y, size, size, WHITE);
}