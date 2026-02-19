#include "model.h"



Model::Model() : pacman(0.0f, 0.0f, 0.09f, 1.0f, 1.0f, 0.0f, true)
{
    // Initialize data here later
    //buildDots();
    pacman.setSpeed(1.0f);

    // create ghosts
    ghosts.emplace_back(randFloat(),randFloat(), 0.06f, randFloat(), randFloat(), randFloat());
    ghosts.back().setSpeed(0.4f);
    ghosts.back().setDirection(0.8f); // radians

    ghosts.emplace_back(randFloat(), randFloat(), 0.06f, randFloat(), randFloat(), randFloat());
    ghosts.back().setSpeed(0.3f);
    ghosts.back().setDirection(0.8f); // radians

    // create fruits
    fruits.emplace_back(randFloat(), randFloat(), 0.025f, randFloat(), randFloat(), randFloat());
    fruits.back().setSpeed(0.4f);
    fruits.back().setDirection(0.8f); // radians

    fruits.emplace_back(randFloat(), randFloat(), 0.025f, randFloat(), randFloat(), randFloat());
    fruits.back().setSpeed(0.3f);
    fruits.back().setDirection(0.8f); // radians
}

Model::~Model()
{
    // Cleanup if needed
}

void Model::buildDots()
{
    // where I want the border to be
    float d = (.85 - -.85) / 11;

    for (int i = 0; i < 12;  i += 1)
    {
        float y = -.85 + i * d;
        for (int j = 0; j < 12;  j += 1)
        {
            float x = -.85 + j * d;
            dots.emplace_back(Dot(x, y, 0.035, 0.6, 0.0, 1.0, true));
        }
    }
}

float Model::randFloat()
{
   // thread_local keeps one RNG per thread; static keeps it initialized once.
    thread_local std::mt19937 rng{ std::random_device{}() };
    thread_local std::uniform_real_distribution<float> dist(-0.95f, 0.95f);

    return dist(rng);
}


std::vector<Entity> Model::getEntities()
{
    return entities;
}

std::vector<Dot> Model::getDots()
{
    return dots;
}

std::vector<Ghost> Model::getGhosts()
{
    return ghosts;
}

std::vector<Fruit> Model::getFruit()
{
    return fruits;
}


void Model::update(float dt)
{
    pacman.update(dt);
    for (auto& g : ghosts)
        g.update(dt);
    for (auto& f : fruits)
        f.update(dt);
}
