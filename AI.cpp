#include "AI.h"

std::pair<int, int> AI::doMove() {
    analyseSituation();
    return possibleMove;
}

void AI::analyseSituation() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (tiedModel -> isFree(i, j)) {
                possibleMove = {i, j};
                return;
            }
        }
    }
}