#include "SteeringBehaviorScene.hpp"

void SteeringBehaviorScene::handleinput()
{

}

void SteeringBehaviorScene::update(const float& dt)
{
    const glm::vec3& mousePos = Mouse::getPosition();
    for (size_t i = 0; i < characters.size(); i++)
    {
        characters[i].flock(characters);
        if (glm::length(glm::vec3(characters[i].pos, 0) - mousePos) < 50.f)
        {
            characters[i].apply(characters[i].flee(mousePos) * 10.f);
        }
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
