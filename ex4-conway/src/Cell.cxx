#include "Cell.h"

Cell::Cell() {
    isAlive = false;
}

void Cell::SetDead() {
    isAlive = false;
}

void Cell::SetAlive() {
    isAlive = true;
}

bool Cell::DetermineLife(int nearbyCount) {
    bool life = false;
    if(!isAlive && nearbyCount == 3)
        life = true;
    else if(isAlive && (nearbyCount == 3 || nearbyCount == 2))
        life = true;
    return life;
}

const bool Cell::GetStatus() const {
    return isAlive;
}
