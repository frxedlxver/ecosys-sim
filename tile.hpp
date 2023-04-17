//
// Created by rhend on 2023-04-15.
//

#ifndef ECOSYS_SIM_TILE_HPP
#define ECOSYS_SIM_TILE_HPP

#include <iostream>
using std::ostream;

class Humanoid;
class Map;

class Tile {
protected:
    int xPos;
    int yPos;
    bool wall;
    Humanoid *occupant;
    Map *map;

public:
    Tile();
    Tile(int xPos, int yPos, Map *map);
    void setOccupant(Humanoid * humanoid);
    Humanoid *getOccupant();
    void clearOccupant();
    [[nodiscard]] bool isWall() const;
    [[nodiscard]] int getXPos() const;
    [[nodiscard]] int getYPos() const;
    [[nodiscard]] bool isEmpty() const;
    friend ostream& operator<<(ostream &output, Tile *tile );
};


#endif //ECOSYS_SIM_TILE_HPP
