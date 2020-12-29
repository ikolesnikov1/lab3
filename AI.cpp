#include "AI.h"
#include <vector>

enum Danger {
    LINE_1,
    LINE_2,
    LINE_3,
    COLUMN_1,
    COLUMN_2,
    COLUMN_3,
    DIAGONAL_1,
    DIAGONAL_2,
    NO_DANGER
};

std::pair<int, int> AI::doMove() {
    analyseSituation();
    return possibleMove;
}

Danger searchForDanger(char field[3][3], char friendSign) {
    char oppositeSign = (friendSign == 'x' ? 'o' : 'x');

    std::vector <std::pair <int, int> > oppositeFields;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i][j] == oppositeSign) {
                oppositeFields.push_back({i, j});
            }
        }
    }

    for (int i = 0; i < oppositeFields.size(); i++) {
        for (int j = i + 1; j < oppositeFields.size(); j++) {
            if (oppositeFields[i].first == oppositeFields[j].first) {
                for (int k = 0; k < 3; k++) {
                    if (field[oppositeFields[i].first][k] == oppositeSign) {
                        continue;
                    } else if (field[oppositeFields[i].first][k] == ' ') {
                        switch (oppositeFields[i].first) {
                            case 0:
                                return LINE_1;
                            case 1:
                                return LINE_2;
                            case 2:
                                return LINE_3;
                            default:
                                return NO_DANGER;
                        }
                    } else {
                        break;
                    }
                }
            } else if (oppositeFields[i].second == oppositeFields[j].second) {
                for (int k = 0; k < 3; k++) {
                    if (field[k][oppositeFields[i].second] == oppositeSign) {
                        continue;
                    } else if (field[k][oppositeFields[i].second] == ' ') {
                        switch (oppositeFields[i].second) {
                            case 0:
                                return COLUMN_1;
                            case 1:
                                return COLUMN_2;
                            case 2:
                                return COLUMN_3;
                            default:
                                return NO_DANGER;
                        }
                    } else {
                        break;
                    }
                }
            } else if (oppositeFields[i].first == oppositeFields[i].second && oppositeFields[j].first == oppositeFields[j].second) {
                for (int k = 0; k < 3; k++) {
                    if (field[k][k] == oppositeSign) {
                        continue;
                    } else if (field[k][k] == ' ') {
                        return DIAGONAL_1;
                    } else {
                        break;
                    }
                }
            } else if (oppositeFields[i].first == 2 - oppositeFields[i].second && oppositeFields[j].first == 2 - oppositeFields[j].second) {
                for (int k = 0; k < 3; k++) {
                    if (field[k][2 - k] == oppositeSign) {
                        continue;
                    } else if (field[k][2 - k] == ' ') {
                        return DIAGONAL_2;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    return NO_DANGER;
}

std::pair <int, int> searchForPossibilities(char field[3][3], char friendSign) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i][j] == ' ') {
                return {i + 1, j + 1};
            }
        }
    }
    return {-1, -1};
}

void AI::analyseSituation() {
    char field[3][3];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            field[i][j] = tiedModel -> getFrom(i, j);
        }
    }
    Danger newDanger = searchForDanger(field, sign);
    switch (newDanger) {
        case LINE_1:
            for (int i = 0; i < 3; i++) {
                if (tiedModel -> getFrom(0, i) == ' ') {
                    possibleMove = {0, i};
                    return;
                }
            }
        case LINE_2:
            for (int i = 0; i < 3; i++) {
                if (tiedModel -> getFrom(1, i) == ' ') {
                    possibleMove = {1, i};
                    return;
                }
            }
        case LINE_3:
            for (int i = 0; i < 3; i++) {
                if (tiedModel -> getFrom(2, i) == ' ') {
                    possibleMove = {2, i};
                    return;
                }
            }
        case COLUMN_1:
            for (int i = 0; i < 3; i++) {
                if (tiedModel -> getFrom(i, 0) == ' ') {
                    possibleMove = {i, 0};
                    return;
                }
            }
        case COLUMN_2:
            for (int i = 0; i < 3; i++) {
                if (tiedModel -> getFrom(i, 1) == ' ') {
                    possibleMove = {i, 1};
                    return;
                }
            }
        case COLUMN_3:
            for (int i = 0; i < 3; i++) {
                if (tiedModel -> getFrom(i, 2) == ' ') {
                    possibleMove = {i, 2};
                    return;
                }
            }
        case DIAGONAL_1:
            for (int i = 0; i < 3; i++) {
                if (tiedModel -> getFrom(i, i) == ' ') {
                    possibleMove = {i, i};
                    return;
                }
            }
        case DIAGONAL_2:
            for (int i = 0; i < 3; i++) {
                if (tiedModel -> getFrom(i, 2 - i) == ' ') {
                    possibleMove = {i, 2 - i};
                    return;
                }
            }
        case NO_DANGER:
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (tiedModel -> getFrom(i, j) == ' ') {
                        possibleMove = {i, j};
                        return;
                    }
                }
            }
    }
}