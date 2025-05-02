#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

bool gameOver;
const int width = 30;
const int height = 20;
int x, y, fruitX, fruitY, score;
vector<pair<int, int>> snake;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    snake.clear();
    snake.push_back({x, y});
}

void Draw() {
    system("cls"); // Clear the console
    
    // Draw top border
    cout << "\033[1;36m"; // Cyan color
    cout << "+";
    for (int i = 0; i < width; i++)
        cout << "-";
    cout << "+" << endl;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) {
                cout << "\033[1;36m"; // Cyan color
                cout << "|";
            }
            
            if (i == y && j == x) {
                cout << "\033[1;32m"; // Green color
                cout << "O"; // Snake head
            } else if (i == fruitY && j == fruitX) {
                cout << "\033[1;31m"; // Red color
                cout << "@"; // Fruit
            } else {
                bool isBody = false;
                for (auto segment : snake) {
                    if (segment.first == j && segment.second == i && !(segment.first == x && segment.second == y)) {
                        cout << "\033[1;32m"; // Green color
                        cout << "o"; // Snake body
                        isBody = true;
                        break;
                    }
                }
                if (!isBody) {
                    cout << " ";
                }
            }
            
            if (j == width - 1) {
                cout << "\033[1;36m"; // Cyan color
                cout << "|";
            }
        }
        cout << endl;
    }
    
    // Draw bottom border
    cout << "+";
    for (int i = 0; i < width; i++)
        cout << "-";
    cout << "+" << endl;
    
    // Draw score
    cout << "\033[1;33m"; // Yellow color
    cout << "Score: " << score << endl;
    cout << "\033[0m"; // Reset color
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT)
                dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN)
                dir = UP;
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    // Save previous tail position
    int prevX = snake.back().first;
    int prevY = snake.back().second;
    
    // Move snake body (from tail to head)
    for (int i = snake.size() - 1; i > 0; i--) {
        snake[i].first = snake[i-1].first;
        snake[i].second = snake[i-1].second;
    }
    
    // Move head
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
    }
    
    // Update head position
    snake[0].first = x;
    snake[0].second = y;
    
    // Check if snake hit the wall
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;
    
    // Check if snake hit itself
    for (int i = 1; i < snake.size(); i++) {
        if (snake[i].first == x && snake[i].second == y)
            gameOver = true;
    }
    
    // Check if snake ate fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        
        // Add new segment to snake at previous tail position
        snake.push_back({prevX, prevY});
        
        // Place new fruit
        fruitX = rand() % width;
        fruitY = rand() % height;
        
        // Make sure fruit doesn't spawn on snake
        bool fruitOnSnake;
        do {
            fruitOnSnake = false;
            for (int i = 0; i < snake.size(); i++) {
                if (fruitX == snake[i].first && fruitY == snake[i].second) {
                    fruitX = rand() % width;
                    fruitY = rand() % height;
                    fruitOnSnake = true;
                    break;
                }
            }
        } while (fruitOnSnake);
    }
}

int main() {
    // Initialize random seed
    srand(time(0));
    
    Setup();
    
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Control game speed
    }
    
    // Game over message
    cout << "\033[1;31m"; // Red color
    cout << "GAME OVER!" << endl;
    cout << "\033[1;33m"; // Yellow color
    cout << "Final Score: " << score << endl;
    cout << "\033[0m"; // Reset color
    
    return 0;
}