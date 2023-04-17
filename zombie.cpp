//
// Created by rhend on 2023-04-15.
//

#include <random>
#include "zombie.hpp"
#include "map.hpp"
#include "tile.hpp"
#include "humanoid.hpp"
#include "human.hpp"
#include "humanoid_controller.hpp"


using std::random_device;

Zombie::Zombie(shared_ptr<Tile> position, Map *map, int id)
    : Humanoid(position, map, id), framesSinceEating(0) {}


void Zombie::act() {

    // will eat if possible, return true if eats, false if not
    // will wander if not
    auto curTile = map->getTile(xPos, yPos);
    if (!this->eat() && this->canMove()) {
        this->move(map->getRandomAdjacentEmptyTile(curTile));
    }

    // if this reaches starving point, mark for death
    if (isStarving()) {
        this->die();
    }
}



Human * Zombie::getTarget() {
    auto curTile = map->getTile(xPos, yPos);
    vector<Human *> *tilesWithHumans = map->getAdjacentHumans(curTile);
    if(tilesWithHumans->size() > 0) {
        int idx = rand() % tilesWithHumans->size();
        return tilesWithHumans->at(idx);
    } else {
        return nullptr;
    }
}


bool Zombie::isHuman() const {
    return false;
}


bool Zombie::isStarving() const {
    return framesSinceEating >= MOVES_UNTIL_STARVE;
}


void Zombie::procreate(HumanoidController *controller) {
    Human *target = getTarget();
    if(target) {
        controller->transformHumanoid(target);
        framesSinceLastProcreation = 0;
    }
}


bool Zombie::readyToProcreate() {
    return framesSinceLastProcreation >= MOVES_UNTIL_BREED;
}

bool Zombie::eat() {
    Human* target = getTarget();
    if(target != nullptr) {
        this->framesSinceEating = 0;
        target->die();
        return true;
    } else {
        return false;
    }
}

void Zombie::passTime() {
    framesSinceEating++;
    framesSinceLastProcreation++;
}
