#ifndef MODEL_H
#define MODEL_H


#include "../entities/dot.h"
#include "../entities/entity.h"


class Model
{
private:
    // Add data members later (game state, objects, etc.)
    std::vector<Dot> dots;
    std::vector<Polygon> polygons;
    std::vector<Entity> entities;

public:
    // Constructor
    Model();

    // Destructor
    ~Model();
    
    void buildDots();
    std::vector<Entity> getEntities();
    std::vector<Dot> getDots();

};

#endif // MODEL_H
