#include <iostream>
#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

const int boardWidth = 10;
const int boardHeight = 20;

int board[boardHeight][boardWidth] = {0};

class Tetris {
public:
    Tetris();
    void drawBoard();
    void drawTetromino();
    void moveTetromino(int direction);
    void rotateTetromino();
    bool isCollision();
    void placeTetromino();
    void clearLines();
    void update();
    char getInput();

private:
    int tetromino;
    int tetrominoX, tetrominoY;
    int speed;
    clock_t lastMove;
};

Tetris::Tetris() {
    srand(static_cast<unsigned int>(time(0)));
    tetromino = rand() % 7;
    tetrominoX = boardWidth / 2;
    tetrominoY = 0;
    speed = 500;
    lastMove = clock();
}

void Tetris::drawBoard() {
    system("clear");
    for (int i = 0; i < boardHeight; ++i) {
        for (int j = 0; j < boardWidth; ++j) {
            if (board[i][j] == 0) cout << ".";
            else cout << "#";
        }
        cout << endl;
    }
}

void Tetris::drawTetromino() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if ((tetromino & (1 << (i * 4 + j))) != 0) {
                board[tetrominoY + i][tetrominoX + j] = 1;
            }
        }
    }
}

void Tetris::moveTetromino(int direction) {
    tetrominoX += direction;
    if (isCollision()) tetrominoX -= direction;
}

void Tetris::rotateTetromino() {
    int tempTetromino = tetromino;
    tetromino = (tetromino >> 12) | ((tetromino & 0xFFF) << 4);
    if (isCollision()) tetromino = tempTetromino;
}

bool Tetris::isCollision() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if ((tetromino & (1 << (i * 4 + j))) != 0) {
                if (tetrominoX + j < 0 || tetrominoX + j >= boardWidth ||
                    tetrominoY + i >= boardHeight || board[tetrominoY + i][tetrominoX + j] != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Tetris::placeTetromino() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if ((tetromino & (1 << (i * 4 + j))) != 0) {
                board[tetrominoY + i][tetrominoX + j] = 1;
            }
        }
    }
}

void Tetris::clearLines() {
    for (int i = boardHeight - 1; i >= 0; --i) {
        int count = 0;
        for (int j = 0; j < boardWidth; ++j) {
            if (board[i][j] != 0) count++;
            board[i][j] = (i - count >= 0) ? board[i - count][j] : 0;
        }
    }
}

void Tetris::update() {
    clock_t now = clock();
    if (static_cast<double>(now - lastMove) / CLOCKS_PER_SEC * 1000 >= speed) {
        tetrominoY++;
        if (isCollision()) {
            tetrominoY--;
            placeTetromino();
            clearLines();
            tetromino = rand() % 7;
            tetrominoX = boardWidth / 2;
            tetrominoY = 0;
        }
        lastMove = now;
    }
}

char Tetris::getInput() {
    char key;
    cin >> key;
    return key;
}

int main() {
    Tetris tetris;

    while (true) {
        tetris.drawBoard();
        tetris.drawTetromino();

        char key = tetris.getInput();

        switch (key) {
            case 'a':
                tetris.moveTetromino(-1);
                break;
            case 'd':
                tetris.moveTetromino(1);
                break;
            case 's':
                tetris.update();
                break;
            case 'w':
                tetris.rotateTetromino();
                break;
            case 'q':
                exit(0);
        }
    }

    return 0;
}
