#pragma once
#include <utility>

class Player {
public:
    char sign = 'x';
    virtual std::pair<int, int> doMove() = 0;
};