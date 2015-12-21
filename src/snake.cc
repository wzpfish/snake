#include "snake.h"
#include <glog/logging.h>

bool SnakeNode::equal(std::size_t x, std::size_t y) {
    return (x_ == x && y_ == y);
}

void Snake::addHead(std::pair<std::size_t, std::size_t> headPoint) {
    SnakeNode *head = new SnakeNode(headPoint.first, headPoint.second);
    if (head_ == nullptr) {
        head_ = head;
        tail_ = head;
    }
    else {
        head_->next_ = head;
        head->pre_ = head_;
        head_ = head;
    }
}

std::pair<std::size_t, std::size_t> Snake::delTail() {
    CHECK(tail_ != nullptr) << "Try to delete tail of null snake";
    std::pair<std::size_t, std::size_t> tail = {tail_->x_, tail_->y_};
    SnakeNode *next = tail_->next_;
    delete tail_; 
    if (next) {
        tail_ = next;
        tail_->pre_ = nullptr;
    }
    else {
        tail_ = nullptr;
        head_ = nullptr; 
    }
    return tail;
}

bool Snake::pointOnSnake(std::size_t x, std::size_t y) {
    for (SnakeNode *head = head_; head != nullptr; head = head->pre_) {
        if (head->equal(x, y)) {
            return true;
        }
    }
    return false;
}

bool Snake::pointOnSnake(std::pair<std::size_t, std::size_t> point) {
    return pointOnSnake(point.first, point.second);
}

std::pair<std::size_t, std::size_t> Snake::getHead() {
    return {head_->x_, head_->y_};
}
