//
// Created by rhend on 2023-04-15.
//

#include "humanoid_controller.hpp"
#include "tile.hpp"
#include "map.hpp"
#include "humanoid.hpp"
#include "human.hpp"
#include "zombie.hpp"
#include "game_settings.hpp"


using std::pair;

// constructor
HumanoidController::HumanoidController(Map *map) : map(map) {
    this->nextHumanoidId = 0;
    this->zombieCount = 0;
    this->humanCount = 0;
    this->totalZombiesAllTime = 0;
    this->totalHumansAllTime = 0;
    this->humanoids = unordered_map<int, Humanoid *>();

    // spawn entities
    for (int i = 0; i < INITIAL_HUMAN_COUNT; i++) {
        spawnHumanOnEmptyTile();
    }
    for (int i = 0; i < INITIAL_ZOMBIE_COUNT; i++) {
        spawnZombieOnEmptyTile();
    }
}


void HumanoidController::destroyHumanoid(Humanoid *h) {
    if (h) {
        h->getPosition()->clearOccupant();
        this->humanoids.erase(h->getId());
        if(h->isHuman()) {
            this->humanCount -= 1;
        } else {
            this->zombieCount -= 1;
        }
    }
}


// returns the id that the tracker should use next
int HumanoidController::getNextId() {
    return this->nextHumanoidId;
}


// main loop to process actions for each humanoid in the sim
void HumanoidController::processFrame() {
    vector<Humanoid *> toKill;
    vector<Humanoid *> toProcreate;

    // for some reason, there are issues with tracking the zombie/human count
    // i've kept the increment/decrement statements in to preserve efficiency
    // this will only exectute if there is a problem, and corrects the count
    // this is a bit of a bandaid solution, as I couldn't find the source of the problem
    // as far as I can tell, the counters are only changed when a humanoid is spawned or destroyed
    // please let me know if you spot the issue!
    if(this->humanCount + this->zombieCount != this->humanoids.size()) {
        this->humanCount = 0;
        this->zombieCount = 0;
        for (auto h : humanoids) {
            if (h.second->isHuman()) {
                this->humanCount++;
            } else {
                this->zombieCount++;
            }
        }
    }

    // game logic loop
    for(auto h : humanoids) {
        if(h.second->isAlive()) {
            h.second->act();
            if (h.second->readyToProcreate()) {
                toProcreate.push_back(h.second);
            }
        } else {
            toKill.push_back(h.second);
        }

        // increments counter for eating, breeding, recruiting
        h.second->passTime();
    }
    for (auto h : toProcreate) {
        h->procreate(this);
    }

    for(auto h : toKill) {
        destroyHumanoid(h);
    }
}


// create a human and assign to a given tile on the map
// !! NOTE !! creating a human without using this function will cause issues with the id system
void HumanoidController::spawnHuman(shared_ptr<Tile> tile) {
    int id = getNextId();
    this->humanoids.insert(pair<int, Humanoid*> (id, new Human(tile, this->map, id)));
    tile->setOccupant(humanoids[id]);
    this->nextHumanoidId += 1;
    this->humanCount += 1;
    this->totalHumansAllTime += 1;
}


// create a human on a random tile on the map
void HumanoidController::spawnHumanOnEmptyTile() {
    spawnHuman(map->getRandomEmptyTile());
}


// create a zombie and assign to a given tile on the map
// !! NOTE !! creating a zombie without using this function will cause issues with the id system
void HumanoidController::spawnZombie(shared_ptr<Tile> tile) {
    int id = getNextId();
    Zombie *newZombie = new Zombie(tile, this->map, id);
    this->humanoids.insert(pair<int, Humanoid*> (id, newZombie));
    tile->setOccupant(humanoids[id]);

    // increment trackers
    this->nextHumanoidId += 1;
    this->zombieCount += 1;
    this->totalZombiesAllTime += 1;
}


// create a zombie on a random tile on the map
void HumanoidController::spawnZombieOnEmptyTile() {
    spawnZombie(this->map->getRandomEmptyTile());
}


// turns a human to a zombie, or a zombie to a human
void HumanoidController::transformHumanoid(Humanoid *humanoid) {

    shared_ptr<Tile> tile = humanoid->getPosition();
    destroyHumanoid(humanoid);

    if(humanoid->isHuman()) {
        spawnZombie(tile);
    } else {
        spawnHuman(tile);
    }
}




bool HumanoidController::extinctionEvent() {
    return this->humanCount <= 0 || this->zombieCount <= 0;
}

int HumanoidController::getCurrentHumanCount() {
    if (this->humanCount < 0) {
        return 0;
    }
    return this->humanCount;
}

int HumanoidController::getCurrentZombieCount() {
    if (this->zombieCount < 0) {
        return 0;
    }
    return this->zombieCount;
}

int HumanoidController::getTotalHumanCount() {
    return this->totalHumansAllTime;
}

int HumanoidController::getTotalZombieCount() {
    return this->totalZombiesAllTime;
}


