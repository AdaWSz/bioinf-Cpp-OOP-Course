#ifndef CELL_H
#define CELL_H


class Cell {
    public:
        Cell();
        const bool GetStatus() const;
        void SetDead();
        void SetAlive();
        bool DetermineLife(int nearbyCount);
    private:
        bool isAlive;
};

#endif
