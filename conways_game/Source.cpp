#include "raylib.h"
#include "cell.h"

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Game Of Life");
	SetWindowState(FLAG_VSYNC_HINT);

	cell(*cells)[screenHeight] = new cell[screenWidth][screenHeight];
	
	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(BLACK);
			
			// When the user clicks Left Mouse button activates that cell
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
				int x = GetMouseX();
				int y = GetMouseY();
				cells[x][y].x = GetMouseX();
				cells[x][y].y = GetMouseY();
				cells[x][y].state = true;
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