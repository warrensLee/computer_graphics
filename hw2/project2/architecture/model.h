#ifndef MODEL_H
#define MODEL_H


//#include "../entities/dot.h"
#include "../entities/entity.h"
#include "../entities/pacman.h"
#include "../entities/ghost.h"
#include "../entities/fruit.h"
#include <tuple>
#include <algorithm>



class Model
{
private:
    // Add data members later (game state, objects, etc.)
    //std::vector<Dot> dots;
    std::vector<Polygon> polygons;
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<Fruit> fruits;
    std::vector<Ghost> ghosts;
    bool gameOver = false;
    float gameOverTimer = 0.0f;

public:
    Pacman* pacmanPtr = nullptr;
    std::mt19937 rng;
    // Constructor
    Model();
    // Destructor
    ~Model();

    struct Color { float r,  g, b; };    
    std::vector<Color> colors;
    std::vector<Color> colorsUsed;

    Color randColor(); 
    float randFloat();
    //void buildDots();
    Pacman& getPacman();

    const std::vector<std::unique_ptr<Entity>>& getEntities() const;    
    std::vector<Ghost> getGhosts();
    //std::vector<Dot> getDots();
    std::vector<Fruit> getFruit();

    bool overlap(const Bounds& a, const Bounds& b);
    void handleCollision(Entity& a, Entity& b);
    void update(float dt);


    int getPacmanLives() const;
    bool getPacmanPower() const;
    bool getPacmanHurt() const;
    bool isGameOver() const;
    float getGameOverTime() const;
    int getPacmanGhostsAte() const;

};

#endif // MODEL_H
