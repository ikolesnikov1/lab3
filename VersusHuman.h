#pragma once
#include "Player.h"

class HumanPlayer : public Player {
public:
    std::pair <int, int> doMove() override;
};