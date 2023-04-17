//
// Created by rhend on 2023-04-15.
//

#ifndef ECOSYS_SIM_ZOMBIE_HPP
#define ECOSYS_SIM_ZOMBIE_HPP

#include "humanoid.hpp"

class Human;

class Zombie : public Humanoid {
private:
    int framesSinceEating;

public:
    Zombie(shared_ptr<Tile> position, Map *map, int id);
    ~Zombie() override {};
    void act() override;
    bool eat();
    Human * getTarget();
    bool isHuman() const override;
    bool isStarving() const;
    void passTime() override;
    void procreate(HumanoidController * controller) override;
    bool readyToProcreate() override;
};


#endif //ECOSYS_SIM_ZOMBIE_HPP
