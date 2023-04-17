//
// Created by rhend on 2023-04-15.
//

#ifndef ECOSYS_HUMANOID_HPP
#define ECOSYS_HUMANOID_HPP

#include <memory>
#include <iostream>
#include <vector>


using std::shared_ptr, std::ostream;

class Tile;
class HumanoidController;
class Map;

class Humanoid {
protected:
    bool alive;
    int id, xPos, yPos;
    int framesSinceLastProcreation;
    Map *map;
public:
    Humanoid(shared_ptr<Tile> position, Map *map, int id);
    virtual ~Humanoid();

    virtual void act() = 0;
    virtual void passTime() = 0;
    bool canMove() const;
    void die();
    shared_ptr<Tile> getPosition();
    int getId();
    bool isAlive();
    virtual bool isHuman() const = 0;
    virtual void move(shared_ptr<Tile> targetTile);
    virtual void procreate(HumanoidController *controller) = 0;
    virtual bool readyToProcreate() = 0;




    friend ostream& operator<<(ostream &output, Humanoid *humanoid );

};


#endif //ECOSYS_HUMANOID_HPP
