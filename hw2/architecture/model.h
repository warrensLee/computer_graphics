#ifndef MODEL_H
#define MODEL_H


#include "../entities/dot.h"
#include "../entities/entity.h"
#include "../entities/pacman.h"
#include "../entities/ghost.h"





class Model
{
private:
    // Add data members later (game state, objects, etc.)
    std::vector<Dot> dots;
    std::vector<Polygon> polygons;
    std::vector<Entity> entities;
    std::vector<Ghost> ghosts;

public:
    Pacman pacman;
    // Constructor
    Model();
    // Destructor
    ~Model();
    
    void buildDots();
    std::vector<Entity> getEntities();
    std::vector<Ghost> getGhosts();
    std::vector<Dot> getDots();

    void update(float dt);

};

#endif // MODEL_H
