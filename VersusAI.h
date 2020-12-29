#pragma once
#include "Player.h"
#include "Context.h"

class VersusAI : public Player {
protected:
    std::pair <int, int> possibleMove;
    Model* tiedModel;

    void analyseSituation();
public:
    explicit VersusAI(Model *model) {
        tiedModel = model;
    }
    std::pair <int, int> doMove() override;
};