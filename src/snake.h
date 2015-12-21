#pragma once

#include <cstddef>
#include <utility>

class Snake;

class SnakeNode {
public:
    friend class Snake;
    SnakeNode() {}
    SnakeNode(std::size_t x, std::size_t y):
        x_(x), y_(y), pre_(nullptr), next_(nullptr) {}
    bool equal(std::size_t, std::size_t);
private:
    std::size_t x_, y_;
    SnakeNode *pre_, *next_;
};

class Snake {
public:
    Snake(): head_(nullptr), tail_(nullptr) {}
    std::pair<std::size_t, std::size_t> getHead();
    void addHead(std::pair<std::size_t, std::size_t>);
    std::pair<std::size_t, std::size_t> delTail();
    bool pointOnSnake(std::size_t, std::size_t);
    bool pointOnSnake(std::pair<std::size_t, std::size_t>);
private:
    SnakeNode *head_;
    SnakeNode *tail_;
    
};
