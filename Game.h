#pragma once
#include "Context.h"

class Game {
    Context ctx;
public:
    void start();
    static void printHelp();
};