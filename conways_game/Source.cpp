#include "raylib.h"
#include "cell.h"
#include <cstdlib>
#include <list>

int main()
{
	const int windowWidth = 800;
	const int windowHeight = 600;

	InitWindow(windowWidth, windowHeight, "Game Of Life");
	SetWindowState(FLAG_VSYNC_HINT);
	
	const int cellSize = 14;
	const int screenWidth = windowWidth / cellSize;
	const int screenHeight = windowHeight / cellSize;

	cell(*cells)[screenHeight] = new cell[screenWidth][screenHeight];
	bool game_running = false;
	std::list<cell> white_cells;

	// Initialize the position of all cells
	for (int j = 0, Y = 0; j < screenHeight; j++, Y+=cellSize) {
		for (int i = 0, X = 0; i < screenWidth; i++, X+=cellSize) {
			cells[i][j].y = Y;
			cells[i][j].x = X;
		}
	}

	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(BLACK);
			DrawFPS(10, 10);
			// When the user clicks Left Mouse button activates that cell
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && !game_running) {
				// Find the closest multiple of cellSize and set x,y to that
				int x = GetMouseX() / cellSize;
				int y = GetMouseY() / cellSize;
				cells[x][y].state = true;

				// Check if the list already contains cells[x][y]
				bool exists = false;
				for (auto itr = white_cells.begin(); itr != white_cells.end(); itr++) {
					if (*itr == cells[x][y])
					{
						exists = true;
					}
				}
				if (!exists) {
					white_cells.push_back(cells[x][y]);
				}
			}

			// If Space is Pressed Start the game of life
			if (IsKeyReleased(KEY_SPACE)) {
				game_running = true;
			}

			// find the no of neighbours of each cell
			if (game_running) {
				/*
				for (int j = 0; j < screenHeight; j++) {
					for (int i = 0; i < screenWidth; i++) {
						int left = abs((i - 1)) % screenWidth;
						int right = abs((i + 1)) % screenWidth;
						int above = abs((j - 1)) % screenHeight;
						int below = abs((j + 1)) % screenHeight;

						if (CheckCollisionRecs(cells[i][j].get_cell(),cells[left][j].get_cell())) {
							cells[i][j].no_of_neighbours++;
						}
						if (CheckCollisionRecs(cells[i][j].get_cell(), cells[right][j].get_cell())) {
							cells[i][j].no_of_neighbours++;
						}
						if (CheckCollisionRecs(cells[i][j].get_cell(), cells[i][above].get_cell())) {
							cells[i][j].no_of_neighbours++;
						}
						if (CheckCollisionRecs(cells[i][j].get_cell(), cells[i][below].get_cell())) {
							cells[i][j].no_of_neighbours++;
						}
					}
				}*/
				/*
				for (auto itr1 = white_cells.begin(); itr1 != white_cells.end(); itr1++) {
					for (auto itr2 = itr1; itr2 != white_cells.end(); ++itr2) {
						if (CheckCollisionRecs(itr1->get_cell(), itr2->get_cell())) {
							(itr1->no_of_neighbours)++;
						}
					}
				}*/
				for (int j = 0; j < screenHeight; j++) {
					for (int i = 0; i < screenWidth; i++) {
						for (auto itr = white_cells.begin(); itr != white_cells.end(); itr++) {
							if (CheckCollisionRecs(cells[i][j].get_cell(), itr->get_cell())) {
								if (*itr != cells[i][j])
									cells[i][j].no_of_neighbours++;
							}
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
							white_cells.push_back(cells[i][j]);
						}
						else {
							cells[i][j].state = false;
							for (auto itr = white_cells.begin(); itr != white_cells.end(); itr++) {
								if (*itr == cells[i][j]) {
									white_cells.erase(itr);
									break;
								}
							}
						}
						// Reset the no of neighbours back to 0
						cells[i][j].no_of_neighbours = 0;
					}
				}
			}
			
			// Draws cells on the screen if state is ON
			for (auto itr = white_cells.begin(); itr != white_cells.end(); itr++) {
				itr->draw();
			}

		EndDrawing();
	}

	white_cells.clear();
	delete[] cells;
	CloseWindow();

	return 0;
}