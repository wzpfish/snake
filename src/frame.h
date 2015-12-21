#pragma once

#include <utility>
#include <vector>
#include "snake.h"

enum Direction{
    UP, DOWN, LEFT, RIGHT
};

class Frame {
public:
    Frame(std::size_t width = 30, std::size_t height = 30);

    std::size_t width() const { return width_; }
    void width(const std::size_t& width) { width_ = width; }
    
    void setPosChar(std::size_t, std::size_t, char c);
    void init();
    void display();
    void randomFood();
    void move();
    bool outOfFrame(std::pair<std::size_t, std::size_t>);
    void changeDir(char);

private:
    std::size_t width_, height_;
    std::size_t food_x_, food_y_;
    Direction dir_;
    std::vector<std::vector<char> > window_;
    Snake snake_;

};
