//
// Created by rhend on 2023-04-15.
//

#ifndef ECOSYS_SIM_HUMANOID_CONTROLLER_HPP
#define ECOSYS_SIM_HUMANOID_CONTROLLER_HPP

#include <tr1/unordered_map>
#include <memory>

using std::tr1::unordered_map, std::shared_ptr;

class Map;
class Tile;
class Humanoid;

class HumanoidController {
private:
    unordered_map<int, Humanoid *> humanoids;
    Map *map;

    // data tracker members
    int nextHumanoidId;
    int humanCount;
    int zombieCount;
    int totalHumansAllTime;
    int totalZombiesAllTime;

public:

    // constructor
    HumanoidController(Map *map);

    // destructor
    ~HumanoidController() = default;

    //other methods
    void destroyHumanoid(Humanoid *h);
    int getCurrentHumanCount();
    int getCurrentZombieCount();
    int getTotalHumanCount();
    int getTotalZombieCount();
    int getNextId();
    void processFrame();
    void spawnHuman(shared_ptr<Tile> tile);
    void spawnHumanOnEmptyTile();
    void spawnZombie(shared_ptr<Tile> tile);
    void spawnZombieOnEmptyTile();
    void transformHumanoid(Humanoid * humanoid);
    bool extinctionEvent();
};


#endif //ECOSYS_SIM_HUMANOID_CONTROLLER_HPP
