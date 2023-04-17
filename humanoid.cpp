//
// Created by rhend on 2023-04-15.
//
#include "humanoid.hpp"
#include "map.hpp"
#include "tile.hpp"
#include "print_color.hpp"

Humanoid::Humanoid(shared_ptr<Tile> position, Map *map, int id)
    : map(map), id(id), alive(true),
    framesSinceLastProcreation(0) {
    this->xPos = position->getXPos();
    this->yPos = position->getYPos();
}

Humanoid::~Humanoid() = default;

void Humanoid::die() {
    this->alive = false;
}


shared_ptr<Tile> Humanoid::getPosition() {
    return map->getTile(xPos, yPos);
}


int Humanoid::getId() {
    return this->id;
}


bool Humanoid::isAlive() {
    return this->alive;
}


// moves humanoid from current tile to specified tile
void Humanoid::move(shared_ptr<Tile> targetTile) {
    auto curTile = this->map->getTile(xPos, yPos);
    if(targetTile && curTile) {
        curTile ->clearOccupant();
        targetTile->setOccupant(this);
        this->xPos = targetTile->getXPos();
        this->yPos = targetTile->getYPos();
    }
}

bool Humanoid::canMove() const {
    auto curTile = this->map->getTile(xPos, yPos);
    return this->map->getRandomAdjacentEmptyTile(curTile) != nullptr;
}

ostream &operator<<(ostream & output, Humanoid *humanoid) {
    if(humanoid->isHuman()) {
        PrintColor::Col(12);
        output << 'H';
    } else {
        PrintColor::Col(1);
        output << 'Z';
    }

    PrintColor::Col(7);
    return output;
}


