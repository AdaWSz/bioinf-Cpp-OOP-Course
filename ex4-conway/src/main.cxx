#include <iostream>
#include <cstdlib>
#include <random>
#include <thread>
#include <atomic>
#include <functional>
#include <chrono>
#include "Display.h"
#include "Grid.h"

int ValidateInput(std::string input) {
    for (int i = 0; i < input.length(); ++i) {
        if (isalpha(input[i])) {
            return 1;
        }
    }
    return 0;
}

std::atomic<bool> keyPressed = false;

void RunSimulation(Grid& grid) {
    while(!keyPressed) {
        RenderFrame(grid.GetData());
        grid.AdvanceTime();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}


int main(int argc, char **argv) {

    long sizeX, sizeY, generation, population;
    bool seedProvided = false;
    long seed;

    if (--argc == 6) {
        std::string userInput;
        int validity;
        for (int x = 1; x <= 7; x=x+2) {
            if (argv[x][0] == 's') {
                userInput = argv[x+1];
                validity = ValidateInput(userInput);
                if (validity == 1) {
                    std::cout << "Invalid seed (must be an integer)" << std::endl;
                    return 0;
                }
                seed = atoi(userInput.c_str());
                seedProvided = true;
            }

            else if (argv[x][0] == 'x') {
                userInput = argv[x+1];
                validity = ValidateInput(userInput);
                if (validity == 1) {
                    std::cout << "Invalid x dimensions (must be an integer)" << std::endl;
                    return 0;
                }
                sizeX = atoi(userInput.c_str());
            }

            else if (argv[x][0] == 'y') {
                userInput = argv[x+1];
                validity = ValidateInput(userInput);
                if (validity == 1) {
                    std::cout << "Invalid y dimensions (must be an integer)" << std::endl;
                    return 0;
                }
                sizeY = atoi(userInput.c_str());
            }

            else {
                std::cout << "Unrecognized argument: " << &argv[x] << std::endl;
                return 0;
            }
        }
    }

    else {
        std::cout << "Provide dimension X for the simulation grid: ";
        std::cin >> sizeX;
        std::cout << "\nProvide dimension Y for the simulation grid: ";
        std::cin >> sizeY;
        std::cout << std::endl;
    }

    if (!seedProvided) {
        std::mt19937 rng(std::random_device{}());
        seed = rng();
    }

    long generationCount;
    Grid grid(sizeX, sizeY, seed);
    grid.GenerateGrid();

    std::thread loopThread = std::thread(RunSimulation, std::ref(grid));
    system("read -n1");
    keyPressed = true;
    loopThread.join();
    return 0;
}
