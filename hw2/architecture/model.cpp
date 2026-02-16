#include "model.h"



Model::Model()
{
    // Initialize data here later
    buildDots();
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
