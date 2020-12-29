#pragma once
#include <utility>

class Player {
public:
    virtual std::pair<int, int> doMove() = 0;
};