#pragma once
#include "Player.h"
#include "Context.h"

class AI : public Player {
protected:
    std::pair <int, int> possibleMove;
    Model* tiedModel;

    void analyseSituation();
public:
    explicit AI(Model *model) {
        tiedModel = model;
    }
    std::pair <int, int> doMove() override;
};