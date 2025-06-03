#pragma once
#include <SFML/Graphics.hpp>
#include "Enums.hpp"

class LevelManager;
class UIManager;
struct Ball;
struct Paddle;
struct Brick;

struct PhysicsManager
{
    bool HandleCollision(ECollisionType inCollisionType, LevelManager& outLvManager);
    void MovePaddle(float deltaTime ,const sf::RenderWindow& inWindow, Paddle& outPaddle);
    void MoveBall(float deltaTime ,const sf::RenderWindow& inWindow, Ball& outBall, UIManager& inUIManager);

private:

    bool HandleCollisionWithBall(const sf::RectangleShape& inShape, LevelManager& outLvManager);
};
