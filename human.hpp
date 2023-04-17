//
// Created by rhend on 2023-04-15.
//

#ifndef ECOSYS_HUMAN_HPP
#define ECOSYS_HUMAN_HPP

#include <memory>
#include "game_settings.hpp"
#include "humanoid.hpp"


using std::shared_ptr;

class Human : public Humanoid {
private:
    static const int MOVES_FOR_RECRUIT = MOVES_UNTIL_RECRUIT;
public:
    Human(shared_ptr<Tile> const& position, Map *map, int id);
    ~Human() override {};

    void act() override;
    bool isHuman() const override;
    bool readyToProcreate() override;
    void procreate(HumanoidController * controller) override;
    void passTime() override;

};


#endif //ECOSYS_HUMAN_HPP
