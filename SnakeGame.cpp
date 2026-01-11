
#include<conio.h>
#include<iostream>
#include<windows.h>
using namespace std;

//width and height of game board
const int width = 80;
const int height = 20;

//Snake head coordinates
int x, y;

//Fruit Coordinates
int fruitCordX, fruitCordY;

//varaiable to store score of the player
int score;

//Array to store coordinates of snake tail
int snakeTailX[100], snakeTailY[100];

//Store length of snake tail
int tailLen;

//Storing snake's moving direction
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
snakesDirection sDir;

//boolean value for checking game is over or not
bool isOver;

//Initialize the Game
void GameInit() {
    isOver = false;
    sDir = STOP;
    x = width / 2;
    y = height / 2;
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    score = 0;
}

//Creating Game board and rendering the game
void GameRender(string playerName) {
    system("cls");     //clear console
    //create top walls
    for (int i = 0; i < width + 2; i++) {
        std::cout << "-";
    }
    std::cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            //creating side walls
            if (j == 0 || j == width) {
                std::cout << "|";
            }
            //creating snake head
            if (i == y && j == x) {
                std::cout << "O";
            }
            //creating fruit
            else if (i == fruitCordY && j == fruitCordX) {
                std::cout << "@";
            }
            else {
                bool print = false;
                for (int k = 0; k < tailLen; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        std::cout << "o";
                        print = true;
                    }
                }
                if (!print) {
                    std::cout << " ";
                }
            }

        }
        std::cout << endl;
    }
    //creating bottom wall
    for (int i = 0; i < width + 2; i++) {
        std::cout << "-";
    }
    std::cout << endl;
    //display player score
    std::cout << playerName << "'s score: " << score << endl;
}

//Updating game state
void UpdateGame() {
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    snakeTailX[0] = x;
    snakeTailY[0] = y;
    int prev2X, prev2Y;
    for (int i = 1; i < tailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (sDir) {
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
    }
    //check for snake's collision with the wall
    if (x >= width || x < 0 || y >= height || y < 0) {
        isOver = true;
    }
    //check for snake's collision with tail
    for (int i = 0; i < tailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y) {
            isOver = true;
        }
    }
    //check for snake collision with fruit
    if (x == fruitCordX && y == fruitCordY) {
        score += 10;
        fruitCordX = rand() %(width);
        fruitCordY = rand() % (height);
        tailLen++;
    }
}

//Set difficulty
int SetDifficulty() {
    int dfc, choice;
    std::cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard\n"
        "NOTE: if not chosen or pressed any other key, the difficulty will be automatically set "
        "to medium\nChoose Difficulty:";
    cin >> choice;
    switch (choice) {
    case 1:
        dfc = 250;
        break;
    case 2:
        dfc = 200;
        break;
    case 3:
        dfc = 150;
        break;
    default:
        dfc = 250;
    }
    return dfc;
}

//handling user input
void UserInput() {
    //check if key is pressed
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            sDir = LEFT;
            break;
        case 'd':
            sDir = RIGHT;
            break;
        case 'w':
            sDir = UP;
            break;
        case 's':
            sDir = DOWN;
            break;
        case 'x':
            isOver = true;
            break;
        }
    }
}

int main() {
    string playerName;
    std::cout << "Enter your Name: ";
    cin >> playerName;
    int dfc = SetDifficulty();
    GameInit();
    while (!isOver) {
        GameRender(playerName);
        UserInput();
        UpdateGame();
        //creating delay according to chosen difficulty
        Sleep(dfc);
    }
    return 0;
}
