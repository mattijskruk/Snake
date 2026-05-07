#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
#pragma comment(lib, "winmm.lib")
bool gameOver;
const int width = 20;
const int height = 20;
int x,y, fruitY, fruitX, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
int tailX[100];
int tailY[100];
int tailCount;
float gameSpeed = 150;
bool tailPrinted;
void Setup() {
    tailCount = 2;
    tailX[0] = 0;
    tailY[0] = 0;
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    tailX[0] = x + 1;
    tailY[0] = y;
    dir = LEFT;
    for (int i = 0; i < 100; i++) {
        tailX[i] = -1;
    }

    tailPrinted = false;
} void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0 ; j < width; j++) {
            if (j == 0) {
                cout << "#";
            }

            if (i == y && j == x) {
                cout << "O";
            }
            else if (i == fruitY && j == fruitX) {
                cout << "F";
            }
            else {
                tailPrinted = false;
                for (int k = 0; k < tailCount - 1; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";  // Tail segment
                        tailPrinted = true;
                        break;
                    }
                    if (x == tailX[k] && y == tailY[k]) {
                        gameOver = true;
                    }
                }

            if  (!tailPrinted) {
                cout << " ";
            }

        }

            if (j == width - 1) {
                cout << "#";
            }
        }
        cout << endl;
    }
    for (int i = 0 ; i < width + 2 ; i++) {
        cout << "#";
    }
    cout << endl;
    cout << "score = " << score << endl;

}
void Input()
{
    if (kbhit()) {
        switch (getch()) {
            case 'a':
                if (dir == RIGHT)
                    break;
                else {
                    dir = LEFT;

                }
                break;
            case 'd':
                if (dir == LEFT) {
                    break;
                }
                else {
                    dir = RIGHT;
                }
                break;
            case 'w':
                if (dir == DOWN)
                    break;
                else {
                    dir = UP;
                }
                break;
            case 's':
                if (dir == UP)
                    break;
                else {
                    dir = DOWN;
                }
                break;
            case 'x':
                gameOver = true;
                break;
            default: break;
        }
    }
} void Logic() {
    for (int l = tailCount; l > 0 - 1; l--) {
        if (l > 0) {
            tailX[l] = tailX[l - 1];
        }
        else {
            tailX[0] = x;
        }
    }
    for (int m = tailCount; m > 0 - 1; m--) {
        if (m > 0) {
            tailY[m] = tailY[m - 1];
        }
        else {
            tailY[0] = y;
        }
    }
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if (x > width || x < 0 || y > height || y < 0) {
        gameOver = true;
    }
    if (x == fruitX && y == fruitY) {
        score += 10;
        tailCount++;
        gameSpeed *= 0.97;
        for (int length = tailCount -1; length > tailCount; length--) {
            if (fruitX == x && fruitY == y && fruitX == x && fruitY == tailX[length] == tailY[length] == fruitY) {
                fruitX = rand() % width;
                fruitY = rand() % height;
            }
            else {
                fruitX = rand() % width;
                fruitY = rand() % height;
            }
        }

    }

}
void Music()
{
    //QString myDir = QFileDialog::getExistingDirectory();
    //PlaySoundA(TEXT("C:\\Users\\matti\\Downloads\\Raze_2 Music_Necromacy.wav"), NULL, SND_FILENAME  | SND_LOOP | SND_ASYNC);
}

int main() {
    Music();
    Setup();
    char yesOrnO = 'y';
    while (yesOrnO == 'y') {
        Setup();
        while (!gameOver) {
            Draw();
            Input();
            Logic();
            Sleep(gameSpeed);
        }
        cout << "Do you want to play again?";
        cin >> yesOrnO;
        gameSpeed = 150;
        gameOver = false;
    }
    return 0;
}