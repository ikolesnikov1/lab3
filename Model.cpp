#include "Context.h"
#include "WrongMove.h"

bool Model::isFree(int first, int second) {
    return field[first][second] == ' ';
}

States Model::getState() {
    return state;
}

char Model::getFrom(int i, int j) {
    return field[i][j];
}

void Model::setState(States _state) {
    state = _state;

    std::cout << "Final result:" << std::endl;
}

void Model::setTo(int i, int j) {
    if (i < 0 || i > 2 || j < 0 || j > 2 || !isFree(i, j)) {
        throw WrongMove();
    }
    field[i][j] = curMove;
    curMove = (curMove == 'x' ? 'o' : 'x');

    synchronize();
}

int checkLines(char field[3][3]) {
    for (int i = 0; i < 3; ++i) {
        if (field[i][0] == field[i][1] && field[i][1] == field[i][2] && field[i][0] != ' ') {
            return i;
        }
    }

    return -1;
}

int checkColumns(char field[3][3]) {
    for (int i = 0; i < 3; ++i) {
        if (field[0][i] == field[1][i] && field[1][i] == field[2][i] && field[0][i] != ' ') {
            return i;
        }
    }

    return -1;
}

int checkDiagonals(char field[3][3]) {
    bool main = field[0][0] == field[1][1] &&
                field[1][1] == field[2][2] &&
                field[0][0] != ' ';

    bool collateral = field[2][0] == field[1][1] &&
                      field[1][1] == field[0][2] &&
                      field[1][1] != ' ';

    if (main) {
        return 1;
    } else if (collateral) {
        return 2;
    }

    return -1;
}

bool Model::isGameEnded() {
    int val;
    if ((val = checkLines(field)) >= 0) {
        if (field[val][0] == 'x') {
            setState(X_WINS);
        } else {
            setState(O_WINS);
        }
    }

    if ((val = checkColumns(field)) >= 0) {
        if (field[0][val] == 'x') {
            setState(X_WINS);
        } else {
            setState(O_WINS);
        }
    }

    if ((val = checkDiagonals(field)) == 1) {
        if (field[0][0] == 'x') {
            setState(X_WINS);
        } else {
            setState(O_WINS);
        }
    } else if (val == 2) {
        if (field[2][0] == 'x') {
            setState(X_WINS);
        } else {
            setState(O_WINS);
        }
    }

    if (state == IN_PROGRESS) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (field[i][j] == ' ') {
                    return false;
                }
            }
        }
        state = DRAW;
    }

    endGameIfOver();

    return true;
}

void Model::addObserver(Viewer viewer) {
    observers.push_back(viewer);
}

void Model::synchronize() {
    for (Viewer viewer : observers) {
        viewer.display(*this);
    }
}

Signs Model::getSign() {
    return (curMove == 'x' ? MARKS : ZEROS);
}

void Model::endGameIfOver() {
    switch (getState()) {
        case IN_PROGRESS:
            return;
        case X_WINS:
            std::cout << "X wins" << std::endl;
            return;
        case O_WINS:
            std::cout << "0 wins" << std::endl;
            return;
        case DRAW:
            std::cout << "Draw" << std::endl;
            return;
    }
}