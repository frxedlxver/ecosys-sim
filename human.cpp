//
// Created by rhend on 2023-04-15.
//

#include "human.hpp"
#include "map.hpp"
#include "humanoid_controller.hpp"

Human::Human(shared_ptr<Tile> const&
        position, Map *map, int id) : Humanoid(position, map, id) {}

void Human::act() {
    if(canMove()) {
        auto curTile = this->map->getTile(xPos, yPos);
        move(map->getRandomAdjacentEmptyTile(curTile));
    }
}

bool Human::readyToProcreate() {
    return framesSinceLastProcreation >= MOVES_FOR_RECRUIT && canMove();
}

bool Human::isHuman() const {
    return true;
}

void Human::procreate(HumanoidController *controller) {
    auto curTile = map->getTile(xPos, yPos);
    auto targetTile = map->getRandomAdjacentEmptyTile(curTile);
    if(targetTile && curTile) {
        controller->spawnHuman(targetTile);
        framesSinceLastProcreation = 0;
    }
}

void Human::passTime() {
    framesSinceLastProcreation ++;
}

