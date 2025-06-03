/* preprocessor directive
*  ensure .h file included only once in a single compilation
*  serves the same purpose as #include guards, but with several advantages
*  including less code, avoidance of name clashes, and sometimes improvement in compilation speed
*/
#pragma once

#include <SFML/Graphics.hpp>
#include "Enums.hpp"

class UIManager;

struct Paddle : sf::RectangleShape
{
    float MoveSpeed;
    
    Paddle();
    Paddle(float inNewWidth, float inNewSpeed);
};

struct Ball : sf::CircleShape
{
    sf::Vector2f Velocity;
    float VelocityModifier;
    
    Ball();
};

struct Brick : sf::RectangleShape
{
    bool IsCollided = false;
};

struct Grid
{
    std::vector<std::vector<Brick>> bricks;
    
    Grid();
};

class LevelManager
{
    Grid grid = Grid();
    Paddle paddle = Paddle();
    Ball ball = Ball();
    float stallTimer = 0.f;
    sf::Font font = sf::Font();
    sf::Text currScoreText = sf::Text(font);
    sf::Text highScoreText = sf::Text(font);
    
public:
    bool isLvClr = true;
    uint8_t currentScore = 0;
    uint8_t highestScore = 0;
    
    LevelManager();
    bool StallBeforeGame(float deltaTime, float stallTime, sf::RenderWindow& inWindow, UIManager& outUIManager);
    void Update(sf::RenderWindow& inWindow, UIManager& outUIManager);
    void Reset();
    void ResetStallTimer() { stallTimer = 0.f; }
    void RestartCurrentLv(const Grid& inGridSnapshot);
    void NextLv(float inPaddleWidth, float inBallVelMod);
    void writeHighestScoreToTxt(const std::string& inFileName);
    void readHighestScoreFromTxt(const std::string& inFileName);
    void SetupScoreboardText(EScoreType inScoreType, unsigned int inTextSize, const sf::Color& inColor, const sf::Vector2f& inPos);
    void UpdateScoreboardText();
    
    Grid& GetGrid() { return grid; }
    const Grid& GetGrid() const { return grid; }
    Paddle& GetPaddle() { return paddle; }
    const Paddle& GetPaddle() const  { return paddle; }
    Ball& GetBall() { return ball; }
    const Ball& GetBall() const { return ball; }
    const Grid& GrabGridSnapshot() const { return grid; }
    sf::Text& GetCurrentScoreText() { return currScoreText; }
    const sf::Text& GetCurrentScoreText() const { return currScoreText; }
    sf::Text& GetHighestScoreText() { return highScoreText; }
    const sf::Text& GetHighestScoreText() const { return highScoreText; }
};

