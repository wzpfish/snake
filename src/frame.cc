#include "frame.h"
#include <glog/logging.h>
#include <iostream>
#include <ctime>


Frame::Frame(std::size_t width, std::size_t height) {
    CHECK_LE(width, 60) << "Frame width must less or equal than 60";
    CHECK_GE(width, 30) << "Frame width must greater or equal than 30";
    CHECK_LE(height, 60) << "Frame height must less or equal than 60";
    CHECK_GE(height, 30) << "Frame height must greater or equal than 30";
    width_ = width * 2;
    height_ = height;
    snake_ = Snake();
    dir_ = RIGHT;
} 

void Frame::setPosChar(std::size_t x, std::size_t y, char c) {
    CHECK(c == '-' || c == '*') << "Must set '-' or '*' for window, find " <<  c;
    CHECK_GE(x, 1) << "Position xaxis must greater or equal than 1, find" << x;
    CHECK_LE(x, height_ - 2) << "Position xaxis must less or equal than " << height_ - 2 << ", find" << x;
    CHECK_GE(y, 1) << "Position yaxis must greater or equal than 1, find" << y;
    CHECK_LE(y, width_ - 2) << "Position yaxis must less or equal than " << width_ - 2 << ", find" << y;
    window_[x][y] = c;
}

void Frame::init() {
    // Init the board of frame
    window_ = std::vector<std::vector<char> >(height_, std::vector<char>(width_, ' '));
    for (std::size_t i = 0; i < height_; ++i) {
        window_[i][0] = window_[i][width_ - 1] = '#';
    }
    for (std::size_t i = 0; i < width_; ++i) {
        window_[0][i] = window_[height_ - 1][i] = '#';
    }
    std::size_t x = height_ / 2;
    std::size_t y = width_ / 2; 

    // Add a snake with one point
    snake_.addHead(std::make_pair(x, y));
    window_[x][y] = '-';

    // Add a food
    randomFood();
}

void Frame::display() {
    for (std::size_t i = 0; i < height_; ++i) {
        for (std::size_t j = 0; j < width_; ++j) {
            std::cout << window_[i][j];
        }
        std::cout << std::endl;
    }
}

void Frame::randomFood() {
    srand((unsigned)time(0));
    bool onSnake = true;
    while (onSnake) {
        food_x_ = rand() % (height_ - 2) + 1;
        food_y_ = rand() % (width_ - 2) + 1;
        if (!snake_.pointOnSnake(food_x_, food_y_)) {
            onSnake = false;
        }
    }
    window_[food_x_][food_y_] = '*';
}

void Frame::move() {
    std::pair<std::size_t, std::size_t> headPoint = snake_.getHead();
    switch (dir_) {
        case UP: --headPoint.first; break;
        case DOWN: ++headPoint.first; break;
        case LEFT: --headPoint.second; break;
        case RIGHT: ++headPoint.second; break;
    }
    if (outOfFrame(headPoint) || snake_.pointOnSnake(headPoint)) {
        std::cout << "Game Over." << std::endl;
        exit(0);
    }
    if (headPoint.first == food_x_ && headPoint.second == food_y_) {
        snake_.addHead(headPoint);
        window_[headPoint.first][headPoint.second] = '-';
        randomFood();
    }
    else {
        snake_.addHead(headPoint);
        window_[headPoint.first][headPoint.second] = '-';
        std::pair<std::size_t, std::size_t> tail = snake_.delTail();
        window_[tail.first][tail.second] = ' ';
    }
}

bool Frame::outOfFrame(std::pair<std::size_t, std::size_t> point) {
    if (point.first <= 0 || point.first >= height_ - 1) return true;
    if (point.second <= 0 || point.second >= width_ - 1) return true;
    return false;
}

void Frame::changeDir(char key) { 
    switch (key) {
        case 'w':
            if (dir_ != DOWN) {
                dir_ = UP;
            }
            break;
        case 's':
            if (dir_ != UP) {
                dir_ = DOWN;
            }
            break;
        case 'a':
            if (dir_ != RIGHT) {
                dir_ = LEFT;
            }
            break;
        case 'd':
            if (dir_ != LEFT) {
                dir_ = RIGHT;
            }
            break;
    }
}
