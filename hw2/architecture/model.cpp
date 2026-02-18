#include "model.h"



Model::Model() : pacman(0.0f, 0.0f, 0.08f, 1.0f, 1.0f, 0.0f, true)
{
    // Initialize data here later
    //buildDots();
    pacman.setSpeed(1.0f);

    // create ghosts
    ghosts.emplace_back(-0.5f, 0.5f, 0.07f, 1.0f, 0.0f, 0.0f);
    ghosts.back().setSpeed(0.4f);
    ghosts.back().setDirection(0.8f); // radians

    ghosts.emplace_back(0.6f, -0.3f, 0.07f, 0.0f, 1.0f, 1.0f);
    ghosts.back().setSpeed(0.3f);
    ghosts.back().setDirection(0.8f); // radians
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


void Model::update(float dt)
{
    pacman.update(dt);
    for (auto& g : ghosts)
        g.update(dt);
}
