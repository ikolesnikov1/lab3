#include "Game.h"
#include <memory>
#include "Human.h"
#include "AI.h"


void Game::printHelp() {
    std::cout << "You can choose 2 types of players:" << std::endl;
    std::cout << "1. Human" << std::endl;
    std::cout << "2. AI" << std::endl << std::endl;
}

int defineType(int numberOfPlayer) {
    bool undefined = true;
    int type;

    while (undefined) {

        std::cout << "Enter the type of player " << numberOfPlayer << ": " << std::endl;
        std::cin >> type;
        if (type > 2 || type < 1) {
            std::cout << "Wrong type!" << std::endl;
            continue;
        }

        undefined = false;
    }

    return type;
}

void Game::start() {
    std::unique_ptr<Player> first;
    std::unique_ptr<Player> second;

    printHelp();

    int firstOption = defineType(1);
    int secondOption = defineType(2);

    switch (firstOption) {
        case 1:
            first = std::make_unique<HumanPlayer>();
            break;
        case 2:
            first = std::make_unique<AI>(&ctx.model);
            break;
        default:
            return;
    }

    switch (secondOption) {
        case 1:
            second = std::make_unique<HumanPlayer>();
            break;
        case 2:
            second = std::make_unique<AI>(&ctx.model);
            break;
        default:
            return;
    }

    ctx.model.addObserver(ctx.viewer);
    while (!ctx.model.isGameEnded()) {
        std::pair <int, int> move;
        std::cout << "Now the move of " << (ctx.model.getSign() == MARKS ? 'x' : 'o') << std::endl;

        if (ctx.model.getSign() == MARKS) {
            if (firstOption == 1) {
                std::cout << "Enter your move as <line> <column>: ";
            }
            move = first -> doMove();
        } else {
            if (secondOption == 1) {
                std::cout << "Enter your move as <line> <column>: ";
            }
            move = second -> doMove();
        }

        ctx.controller.updateRequest(move, &ctx.model);
    }
}