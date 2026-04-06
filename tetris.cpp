#include "raylib.h"
#include <iostream>
using namespace std;

#define SQUARE_SIZE 20
#define GRID_W 12
#define GRID_H 20

enum GridSquare { EMPTY, MOVING, FULL, BLOCK };

class Tetris {
private:
    GridSquare grid[GRID_W][GRID_H];
    GridSquare piece[4][4];
    GridSquare incoming[4][4];

    int posX, posY;

    bool pieceActive;
    bool detection;
    bool pause;

    int gravityCounter;
    int gravitySpeed;

public:
    Tetris() { Init(); }

    void Init() {
        pieceActive = false;
        detection = false;
        pause = false;

        posX = 0;
        posY = 0;

        gravityCounter = 0;
        gravitySpeed = 30;

        RandomPiece(incoming);

        for (int i = 0; i < GRID_W; i++) {
            for (int j = 0; j < GRID_H; j++) {
                if (j == GRID_H - 1 || i == 0 || i == GRID_W - 1)
                    grid[i][j] = BLOCK;
                else
                    grid[i][j] = EMPTY;
            }
        }
    }

    void RandomPiece(GridSquare arr[4][4]) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                arr[i][j] = EMPTY;

        int r = GetRandomValue(0, 6);

        switch (r) {
        case 0: arr[1][1] = arr[2][1] = arr[1][2] = arr[2][2] = MOVING; break;
        case 1: arr[1][0] = arr[1][1] = arr[1][2] = arr[2][2] = MOVING; break;
        case 2: arr[1][2] = arr[2][0] = arr[2][1] = arr[2][2] = MOVING; break;
        case 3: arr[0][1] = arr[1][1] = arr[2][1] = arr[3][1] = MOVING; break;
        case 4: arr[1][0] = arr[1][1] = arr[1][2] = arr[2][1] = MOVING; break;
        case 5: arr[1][1] = arr[2][1] = arr[2][2] = arr[3][2] = MOVING; break;
        case 6: arr[1][2] = arr[2][2] = arr[2][1] = arr[3][1] = MOVING; break;
        }
    }

    void ApplyPieceToGrid() {
        for (int i = 0; i < GRID_W; i++)
            for (int j = 0; j < GRID_H; j++)
                if (grid[i][j] == MOVING)
                    grid[i][j] = EMPTY;

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (piece[i][j] == MOVING)
                    grid[posX + i][posY + j] = MOVING;
    }

    void CreatePiece() {
        posX = (GRID_W - 4) / 2;
        posY = 0;

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                piece[i][j] = incoming[i][j];

        RandomPiece(incoming);

        ApplyPieceToGrid();
        pieceActive = true;
    }

    bool CanRotate(GridSquare temp[4][4]) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (temp[i][j] == MOVING) {
                    int x = posX + i;
                    int y = posY + j;

                    if (x <= 0 || x >= GRID_W - 1 || y >= GRID_H)
                        return false;

                    if (grid[x][y] == FULL)
                        return false;
                }
        return true;
    }

    void Rotate() {
        if (!IsKeyPressed(KEY_UP)) return;

        GridSquare temp[4][4];

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                temp[i][j] = piece[3 - j][i];

        if (CanRotate(temp)) {
            for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                    piece[i][j] = temp[i][j];

            ApplyPieceToGrid();
        }
    }

    void Move() {
        if (IsKeyPressed(KEY_LEFT)) posX--;
        if (IsKeyPressed(KEY_RIGHT)) posX++;

        ApplyPieceToGrid();
    }

    void CheckDetection() {
        detection = false;

        for (int j = GRID_H - 2; j >= 0; j--)
            for (int i = 1; i < GRID_W - 1; i++)
                if (grid[i][j] == MOVING &&
                    (grid[i][j + 1] == FULL || grid[i][j + 1] == BLOCK))
                    detection = true;
    }

    void ClearLines() {
        for (int j = 0; j < GRID_H - 1; j++) {
            bool full = true;

            for (int i = 1; i < GRID_W - 1; i++) {
                if (grid[i][j] != FULL) {
                    full = false;
                    break;
                }
            }

            if (full) {
                for (int k = j; k > 0; k--)
                    for (int i = 1; i < GRID_W - 1; i++)
                        grid[i][k] = grid[i][k - 1];

                for (int i = 1; i < GRID_W - 1; i++)
                    grid[i][0] = EMPTY;

                j--;
            }
        }
    }

    void Fall() {
        if (detection) {
            for (int j = 0; j < GRID_H; j++)
                for (int i = 0; i < GRID_W; i++)
                    if (grid[i][j] == MOVING)
                        grid[i][j] = FULL;

            ClearLines();
            pieceActive = false;
        }
        else {
            posY++;
            ApplyPieceToGrid();
        }
    }

    void Update() {
        if (IsKeyPressed('P')) pause = !pause;
        if (pause) return;

        if (!pieceActive) {
            CreatePiece();
            return;
        }

        Move();
        Rotate();

        gravityCounter++;
        if (gravityCounter >= gravitySpeed) {
            CheckDetection();
            Fall();
            gravityCounter = 0;
        }
    }

    void Draw() {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int j = 0; j < GRID_H; j++) {
            for (int i = 0; i < GRID_W; i++) {

                Color c = LIGHTGRAY;

                if (grid[i][j] == FULL) c = GRAY;
                if (grid[i][j] == MOVING) c = DARKGRAY;
                if (grid[i][j] == BLOCK) c = BLACK;

                DrawRectangle(i * SQUARE_SIZE + 200,
                    j * SQUARE_SIZE + 50,
                    SQUARE_SIZE, SQUARE_SIZE, c);
            }
        }

        EndDrawing();
    }
};

int main() {
    InitWindow(800, 450, "Tetris C++ Complete");
    SetTargetFPS(60);

    Tetris game;

    while (!WindowShouldClose()) {
        game.Update();
        game.Draw();
    }

    CloseWindow();
    return 0;
}
