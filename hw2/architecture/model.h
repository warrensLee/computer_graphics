#ifndef MODEL_H
#define MODEL_H


#include "../entities/dot.h"
#include "../entities/entity.h"
#include "../entities/pacman.h"
#include "../entities/ghost.h"
#include "../entities/fruit.h"
#include <random>



class Model
{
private:
    // Add data members later (game state, objects, etc.)
    std::vector<Dot> dots;
    std::vector<Polygon> polygons;
    std::vector<Entity> entities;
    std::vector<Fruit> fruits;
    std::vector<Ghost> ghosts;

public:
    Pacman pacman;
    // Constructor
    Model();
    // Destructor
    ~Model();

    float randFloat();
    void buildDots();

    std::vector<Entity> getEntities();
    std::vector<Ghost> getGhosts();
    std::vector<Dot> getDots();
    std::vector<Fruit> getFruit();

    void update(float dt);

};

#endif // MODEL_H
