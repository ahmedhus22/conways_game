#include "raylib.h"
#include "cell.h"
#include <cstdlib>

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Game Of Life");
	SetWindowState(FLAG_VSYNC_HINT);

	cell(*cells)[screenHeight] = new cell[screenWidth][screenHeight];
	bool game_running = false;
	
	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(BLACK);
			
			// When the user clicks Left Mouse button activates that cell
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && !game_running) {
				int x = GetMouseX();
				int y = GetMouseY();
				cells[x][y].x = GetMouseX();
				cells[x][y].y = GetMouseY();
				cells[x][y].state = true;
			}

			// If Space is Pressed Start the game of life
			if (IsKeyReleased(KEY_SPACE)) {
				game_running = true;
			}

			// find the no of neighbours of each cell
			if (game_running) {
				for (int j = 0; j < screenHeight; j++) {
					for (int i = 0; i < screenWidth; i++) {
						int left = abs((i - 1)) % screenWidth;
						int right = abs((i + 1)) % screenWidth;
						int above = abs((j - 1)) % screenHeight;
						int below = abs((j + 1)) % screenHeight;

						if (cells[left][j].state) {
							cells[i][j].no_of_neighbours++;
						}
						if (cells[right][j].state) {
							cells[i][j].no_of_neighbours++;
						}
						if (cells[i][below].state) {
							cells[i][j].no_of_neighbours++;
						}
						if (cells[i][below].state) {
							cells[i][j].no_of_neighbours++;
						}
					}
				}
			}

			// Game Of Life Rules
			if (game_running) {
				for (int j = 0; j < screenHeight; j++) {
					for (int i = 0; i < screenWidth; i++) {
						// Any live cell with two or three live neighbours survives.
						if ((cells[i][j].no_of_neighbours == 2 || cells[i][j].no_of_neighbours == 3) && cells[i][j].state) {}
						// Any dead cell with three live neighbours becomes a live cell.
						else if (cells[i][j].no_of_neighbours == 3 && !cells[i][j].state) {
							cells[i][j].state = true;
						}
						else {
							cells[i][j].state = false;
						}
					}
				}
			}

			// Draws cells on the screen if state is ON
			for (int j = 0; j < screenHeight; j++) {
				for (int i = 0; i < screenWidth; i++) {
					if (cells[i][j].state) {
						cells[i][j].draw();
					}
				}
			}

		EndDrawing();
	}

	delete[] cells;
	CloseWindow();
	return 0;
}