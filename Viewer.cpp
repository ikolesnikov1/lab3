#include <iostream>
#include "Context.h"

void Viewer::display(Model model) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << model.field[i][j] << " ";
            if (j < 2) {
                std::cout << "|";
            }
        }
        std::cout << std::endl;
        if (i < 2) {
            std::cout <<"-----";
            std::cout << std::endl;
        }
    }

    for (int i = 0; i < 3; ++i) {
        std::cout << std::endl;
    }
}