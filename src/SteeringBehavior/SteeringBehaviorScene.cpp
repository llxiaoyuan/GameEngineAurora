#include "SteeringBehaviorScene.hpp"

std::unique_ptr<Scene> SteeringBehaviorScene::clone()
{
    return std::make_unique<SteeringBehaviorScene>(*this);
}

void SteeringBehaviorScene::handleinput()
{

}

void SteeringBehaviorScene::update(const float& dt)
{
    for (size_t i = 0; i < characters.size(); i++)
    {
        characters[i].flock(characters);
        characters[i].update(dt*200.f);
    }
}

void SteeringBehaviorScene::render(SpriteRenderer* const spriteRenderer, ShapeRenderer* const shapeRenderer)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);
    spriteRenderer->begin();
    for (size_t i = 0; i < characters.size(); i++)
    {
        spriteRenderer->draw(arrow, characters[i].pos.x, characters[i].pos.y, arrow->getWidth() / 2, arrow->getHeight() / 2, atan2f(characters[i].vel.y, characters[i].vel.x));
    }
    spriteRenderer->end();
}
