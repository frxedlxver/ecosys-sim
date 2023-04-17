//
// Created by rhend on 2023-04-15.
//

#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include <stdexcept>
#include "map.hpp"
#include "humanoid.hpp"
#include "human.hpp"
#include "tile.hpp"

using std::shuffle, std::begin, std::end, std::random_device, std::shared_ptr, std::make_shared, std::runtime_error;

Map::Map() {
    this->grid.resize(MAP_HEIGHT + WALLS, vector<shared_ptr<Tile>>(MAP_WIDTH + WALLS));
    this->createGridTiles();
    this->xWallLeft = 0;
    this->yWallTop = 0;
    this->xWallRight = getMapWidth() - 1;
    this->yWallBottom = getMapHeight() - 1;
}


void Map::createGridTiles() {
    for(int y = 0; y < grid.size(); y++) {
        for(int x = 0; x < grid[0].size(); x++) {
            grid[y][x] = make_shared<Tile>(Tile(x, y, this));
        }
    }
}


Map::~Map() {
 for(auto row : grid) {
     for (auto tile : row) {
         tile.reset();
     }
 }
}


shared_ptr<Tile>Map::getTile(int xPos, int yPos) {
    if (!coordInBounds(xPos, yPos)) {
        return nullptr;
    } else {
        return grid[yPos][xPos];
    }
}

shared_ptr<Tile> Map::getRandomAdjacentEmptyTile(shared_ptr<Tile> tile) {
    auto adjacentTiles = getAdjacentEmptyTiles(tile);
    if (!adjacentTiles->empty()) {
        auto targetIdx = (rand() % adjacentTiles->size());
        return adjacentTiles->at(targetIdx );
    }
    return nullptr;

}


shared_ptr<Tile>Map::getRandomEmptyTile() {
    shared_ptr<Tile>result;

    do {
        result = getRandomTile();
    } while (!result->isEmpty());

    return result;
}

// returns a random tile anywhere on the map
shared_ptr<Tile>Map::getRandomTile() {

    auto rng = random_device();

    int xPos = rng.operator()() % MAP_WIDTH + 1;
    int yPos = rng.operator()() % MAP_HEIGHT + 1;

    return grid[yPos][xPos];
}


// used in movement methods
// returns all adjacent tiles EXCEPT walls
vector<shared_ptr<Tile>> *Map::getAdjacentTiles(shared_ptr<Tile> tile) {

    if (tile->isWall()) {
        throw std::runtime_error("Exception: Humanoid on wall tile");
    }

    int x = tile->getXPos();
    int y = tile->getYPos();
    int dist = HUMANOID_MOVEMENT_SPEED;
    auto adjacentTiles = new vector<shared_ptr<Tile>>;
    adjacentTiles->push_back(getTile(x, y + dist));
    adjacentTiles->push_back(getTile(x, y - dist));
    adjacentTiles->push_back(getTile(x + dist, y));
    adjacentTiles->push_back(getTile(x - dist, y));

    auto usableAdjacentTiles = new vector<shared_ptr<Tile>>;
    for (auto t : *adjacentTiles) {
        if (t && !t->isWall()) {
            usableAdjacentTiles->push_back(t);
        }
    }

    delete(adjacentTiles);
    return usableAdjacentTiles;
}


int Map::getMapHeight() {
    return grid.size();
}

int Map::getMapWidth() {
    return grid[0].size();
}

// used by movement methods
// returns all empty adjacent tiles
vector<shared_ptr<Tile>> *Map::getAdjacentEmptyTiles(shared_ptr<Tile> tile) {
    auto adjacentTiles = getAdjacentTiles(tile);
    auto emptyTiles = new vector<shared_ptr<Tile>>();

    for(shared_ptr<Tile>t : *adjacentTiles) {
        if(t->isEmpty()) {
            emptyTiles->push_back(t);
        }
    }

    return emptyTiles;
}



vector<Human *> * Map::getAdjacentHumans(shared_ptr<Tile> tile) {
    auto adjacentTiles = getAdjacentTiles(tile);
    auto adjacentHumans = new vector<Human *>();

    for(shared_ptr<Tile>t : *adjacentTiles) {
        Humanoid *h = t->getOccupant();
        if(h != nullptr && h->isHuman()) {

            adjacentHumans->push_back((dynamic_cast<Human *>(h)));
        }
    }

    return adjacentHumans;
}

bool Map::coordInBounds(int x, int y) {
    return x > xWallLeft && x < xWallRight && y > yWallTop && y < yWallBottom;
}

ostream &operator<<(ostream &output, Map *map) {
    for (auto row : map->grid) {
        for (auto tile : row) {
            output << tile;
        }
        output << '\n';
     }

    return output;
}


