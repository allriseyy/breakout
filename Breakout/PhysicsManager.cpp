#include "PhysicsManager.hpp"
#include "LevelManager.hpp"
#include "UIManager.hpp"

using namespace std;
using namespace sf;

bool PhysicsManager::HandleCollision(ECollisionType inCollisionType, LevelManager& outLvManager)
{
    switch (inCollisionType)
    {
        case ECollisionType::ball_paddle:
        {
                // ball must always be falling down
                if (outLvManager.GetBall().Velocity.y <= 0.f)
                {
                   return false;
                }
                
                return HandleCollisionWithBall(outLvManager.GetPaddle(), outLvManager);
        }
        
        case ECollisionType::ball_bricks:
        {
            for (vector<Brick>& shapes : outLvManager.GetGrid().bricks)
            {
                for (Brick& shape : shapes)
                {
                    // yes there is intersection, but does this specific brick cares about it? if inactive it shouldnt
                    if (!shape.IsCollided && HandleCollisionWithBall(shape, outLvManager))
                    {
                        shape.IsCollided = true;
                        return shape.IsCollided;
                    }
                }
            }
            return false;
        }
    }
    return false;
}

void PhysicsManager::MovePaddle(float deltaTime, const sf::RenderWindow& inWindow, Paddle& outPaddle)
{
    if (isKeyPressed(Keyboard::Key::Left))
    {
        outPaddle.move({-outPaddle.MoveSpeed * deltaTime, 0});
    }
    if (isKeyPressed(Keyboard::Key::Right))
    {
        outPaddle.move({outPaddle.MoveSpeed * deltaTime, 0});
    }

    // paddle bound
    bool isLeftBound = outPaddle.getPosition().x <= 0.f;
    bool isRightBound = outPaddle.getPosition().x + outPaddle.getSize().x >= static_cast<float>(inWindow.getSize().x);
    if (isLeftBound)
    {
        outPaddle.setPosition({0.f, outPaddle.getPosition().y});    
    }
    else if (isRightBound)
    {
        outPaddle.setPosition({(static_cast<float>(inWindow.getSize().x) - outPaddle.getSize().x), outPaddle.getPosition().y});
    }
}

void PhysicsManager::MoveBall(float deltaTime, const sf::RenderWindow& inWindow, Ball& outBall, UIManager& inUIManager)
{
    bool isLeftBound = outBall.getPosition().x <= 0.f;
    bool isRightBound = outBall.getPosition().x >= (static_cast<float>(inWindow.getSize().x) - outBall.getRadius());
    bool isTopBound = outBall.getPosition().y <= 0.f;
    bool isBottomBound = outBall.getPosition().y >= (static_cast<float>(inWindow.getSize().y) - outBall.getRadius());

    // should be impossible for both to be true at the same time
    if ((isLeftBound && outBall.Velocity.x < 0.f) || (isRightBound && outBall.Velocity.x > 0.f))
    {
        // flip the direction
        outBall.Velocity.x *= -1;
    }
    if (isTopBound && outBall.Velocity.y < 0.f)
    {
        // flip y vel back to positive so it will head downward
        outBall.Velocity.y *= -1;
    }
    else if (isBottomBound)
    {
        inUIManager.SetGameOver();
    }
    
     outBall.move(outBall.Velocity * deltaTime * outBall.VelocityModifier);
}

bool PhysicsManager::HandleCollisionWithBall(const RectangleShape& inShape, LevelManager& outLvManager)
{
    if (!static_cast<bool>(outLvManager.GetBall().getGlobalBounds().findIntersection(inShape.getGlobalBounds())))
    {
        return false;
    }
    
    outLvManager.GetBall().Velocity *=  -1.f; // -x , -y - flip both dir by default until told otherwise
    Vector2f ballCenter = outLvManager.GetBall().getGlobalBounds().getCenter();
    Vector2f shapeCenter = inShape.getGlobalBounds().getCenter();
    if (std::fabs(shapeCenter.y - ballCenter.y) <= (inShape.getSize().y / 2))
    {
        // -x ,y - retain x, flip y dir back to ori
        outLvManager.GetBall().Velocity.y *= -1.f;
    }
    else if (std::fabs(shapeCenter.x - ballCenter.x) <= (inShape.getSize().x / 2))
    {
        // x, -y - retain y, flip x dir back to ri
        outLvManager.GetBall().Velocity.x *= -1.f;
    }

    return true;
}
