//
// Created by rhend on 2023-04-15.
//



#ifndef ECOSYS_SIM_MAP_HPP
#define ECOSYS_SIM_MAP_HPP

#include <vector>
#include <memory>
#include <iostream>
#include "game_settings.hpp"

class Tile;
class Human;


using std::vector, std::shared_ptr, std::ostream;

class Map {
private:
    static const int WALLS = 2;
    static const int MAP_WIDTH = GRID_WIDTH;
    static const int MAP_HEIGHT = GRID_HEIGHT;
    int yWallTop;
    int yWallBottom;
    int xWallLeft;
    int xWallRight;
    vector<vector<shared_ptr<Tile>>> grid;
public:
    Map();
    ~Map();


    void createGridTiles();
    bool coordInBounds(int x, int y);
    shared_ptr<Tile>getTile(int xPos, int yPos);
    int getMapHeight();
    int getMapWidth();
    shared_ptr<Tile> getRandomTile();
    shared_ptr<Tile> getRandomEmptyTile();
    shared_ptr<Tile> getRandomAdjacentEmptyTile(shared_ptr<Tile> tile);
    vector<shared_ptr<Tile>> *getAdjacentTiles(shared_ptr<Tile> tile);
    vector<Human *> * getAdjacentHumans(shared_ptr<Tile> tile);

    vector<shared_ptr<Tile>> *getAdjacentEmptyTiles(shared_ptr<Tile> tile);
    friend ostream& operator<<(ostream &output, Map *map);
};


#endif //ECOSYS_SIM_MAP_HPP
