//
// Created by rhend on 2023-04-15.
//

#include "tile.hpp"
#include "map.hpp"
#include "humanoid.hpp"

// default constructor needed for map allocation. don't use this.
Tile::Tile() : xPos(0), yPos(0), wall(true), occupant(nullptr) {}


// normal constructor with parameters
Tile::Tile(int xPos, int yPos, Map *map) : xPos(xPos), yPos(yPos), map(map), occupant(nullptr)
{
    this->wall = (xPos == 0 || yPos == 0 || xPos == map->getMapWidth() - 1 || yPos == map->getMapHeight() - 1);
}


// returns tile occupant
Humanoid *Tile::getOccupant() {
    return occupant;
}


// set tile occupant
void Tile::setOccupant(Humanoid *const humanoid) {
    this->occupant = humanoid;
}


// clear tile occupant
void Tile::clearOccupant() {
    this->occupant = nullptr;
}


// return y position
int Tile::getYPos() const {
    return this->yPos;
}


// return x position
int Tile::getXPos() const {
    return this->xPos;
}


// check if tile has no occupant
bool Tile::isEmpty() const {
    return this->occupant == nullptr;
}


// check if wall
bool Tile::isWall() const {
    return this->wall;
}

ostream &operator<<(ostream &output, Tile *tile) {
    if(!tile->isEmpty()) { // occupied tile, print occupant appearance
        output << tile->occupant;
    } else if (tile->isWall()) { // wall tile
        output << '+';
    } else { // empty tile
        output << '-';
    }

    return output;
}


