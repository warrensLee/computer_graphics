#include "model.h"


    struct Color 
    { 
        float r,  g, b; 
    };    



Model::Model() : rng(std::random_device{}())
{
    colors =
    {
        {1.0f, 0.0f, 0.0f},   // Red
        {0.0f, 1.0f, 0.0f},   // Green
        {0.0f, 0.0f, 1.0f},   // Blue
        {1.0f, 1.0f, 0.0f},   // Yellow
        {1.0f, 0.0f, 1.0f},   // Magenta
        {0.0f, 1.0f, 1.0f},   // Cyan
        {1.0f, 0.5f, 0.0f},   // Orange
        {0.5f, 0.0f, 1.0f}    // Purple
    };

    // remove pacman from initializer list and class members
    entities.push_back(std::make_unique<Pacman>(0.0f, 0.0f, 0.08f, 1.0f, 1.0f, 0.0f, true));

    // store pointer to the actual pacman object
    pacmanPtr = static_cast<Pacman*>(entities.back().get());

    pacmanPtr->setSpeed(0.5f);

    // create ghosts & fruit
    std::shuffle(colors.begin(), colors.end(), rng); //shuffle colors
    Color ghostOne = randColor();
    Color ghostTwo = randColor();
    Color ghostThree = randColor();
    Color fruitOne = randColor();
    Color fruitTwo = randColor();
    Color fruitThree = randColor();

    entities.push_back(std::make_unique<Ghost>(randFloat(),randFloat(), 0.07f, ghostOne.r, ghostOne.g, ghostOne.b, true));
    entities.back()->setSpeed(0.45f);
    entities.back()->setDirection(1.0f); // radians
;

    entities.push_back(std::make_unique<Ghost>(randFloat(), randFloat(), 0.07f, ghostTwo.r, ghostTwo.g, ghostTwo.b, true));
    entities.back()->setSpeed(0.45f);
    entities.back()->setDirection(-1.0f); // radians


    entities.push_back(std::make_unique<Ghost>(randFloat(), randFloat(), 0.07f, ghostThree.r, ghostThree.g, ghostThree.b, true));
    entities.back()->setSpeed(0.45f);
    entities.back()->setDirection(-0.2f); // radians


    // create fruits
   entities.push_back(std::make_unique<Fruit>(randFloat(), randFloat(), 0.02f, fruitOne.r, fruitOne.g, fruitOne.b, true));
    entities.back()->setSpeed(0.5f);
    entities.back()->setDirection(0.5f); // radians

    entities.push_back(std::make_unique<Fruit>(randFloat(), randFloat(), 0.02f, fruitTwo.r, fruitTwo.g, fruitTwo.b, true));
    entities.back()->setSpeed(0.5f);
    entities.back()->setDirection(-0.5f); // radians

    entities.push_back(std::make_unique<Fruit>(randFloat(), randFloat(), 0.02f, fruitThree.r, fruitThree.g, fruitThree.b, true));
    entities.back()->setSpeed(0.5f);
    entities.back()->setDirection(0.2f); // radians
}

Model::~Model()
{
    // Cleanup if needed
}

// void Model::buildDots()
// {
//     // where I want the border to be
//     float d = (.85 - -.85) / 11;

//     for (int i = 0; i < 12;  i += 1)
//     {
//         float y = -.85 + i * d;
//         for (int j = 0; j < 12;  j += 1)
//         {
//             float x = -.85 + j * d;
//             dots.emplace_back(Dot(x, y, 0.035, 0.6, 0.0, 1.0, true));
//         }
//     }
// }

float Model::randFloat()
{
   // thread_local keeps one RNG per thread; static keeps it initialized once.
    thread_local std::mt19937 rng{ std::random_device{}() };
    thread_local std::uniform_real_distribution<float> dist(-0.95f, 0.95f);

    return dist(rng);
}

int Model::getPacmanLives() const
{
    return pacmanPtr->getLives();
}

bool Model::getPacmanPower() const
{
    return pacmanPtr->getPower();

}


bool Model::isGameOver() const 
{ 
    return gameOver; 
}

float Model::getGameOverTime() const 
{ 
    return gameOverTimer; 
}

bool Model::getPacmanHurt() const
{
    return pacmanPtr->getHurt();
}



Model::Color Model::randColor()
{   
    if (colors.empty())
        throw std::runtime_error("No colors available");

    Color c = colors.back();
    colors.pop_back();
    return c;
}

const std::vector<std::unique_ptr<Entity>>& Model::getEntities() const
{
    return entities;
}

// std::vector<Dot> Model::getDots()
// {
//     return dots;
// }

std::vector<Ghost> Model::getGhosts()
{
    return ghosts;
}

std::vector<Fruit> Model::getFruit()
{
    return fruits;
}

void Model::handleCollision(Entity& a, Entity& b)
{
    a.onCollide(b);
    b.onCollide(a);
}

bool Model::overlap(const Bounds& a, const Bounds& b)
{
    return (a.left   < b.right)  &&
           (a.right  > b.left)   &&
           (a.bottom < b.top)    &&
           (a.top    > b.bottom);
}

Pacman& Model::getPacman()
{
    return *pacmanPtr;
}

int Model::getPacmanGhostsAte() const
{
    return pacmanPtr->getGhostsAte();
}


void Model::update(float dt)
{

    if (gameOver)
    {
        gameOverTimer += dt;
        return;
    }

    entities.erase(
    std::remove_if(entities.begin(), entities.end(),
        [](const std::unique_ptr<Entity>& e) {
            return !e->getAlive();   // or !e->alive
        }),
    entities.end()
                );

    for (auto& e : getEntities())
        e->update(dt);

    for (int i = 0; i < (int)entities.size(); i++)
    {
        if (!entities[i]->getAlive()) 
            continue;
        Bounds bi = entities[i]->getBounds();

        for (int j = i + 1; j < (int)entities.size(); j++)
        {
            if (!entities[j]->getAlive()) 
                continue;
            Bounds bj = entities[j]->getBounds();
            if (overlap(bi, bj))
            {
                handleCollision(*entities[i], *entities[j]);
            }
        }
    }

    if (getPacmanLives() <= 0)   // however you access it
    {
        gameOver = true;
        gameOverTimer = 0.0f;
        return;
    }


}
