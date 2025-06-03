#include "LevelManager.hpp"
#include "PhysicsManager.hpp"
#include "UIManager.hpp"
#include "Constants.hpp"

#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

Paddle::Paddle()
    : MoveSpeed(Paddle_Speed)
{
    setSize(sf::Vector2f(Paddle_Width, Paddle_Length));
    setFillColor(sf::Color::Green);
    setPosition(sf::Vector2f(Paddle_Xpos, Paddle_Ypos));
}

Paddle::Paddle(float inNewWidth, float inNewSpeed)
    : MoveSpeed(inNewSpeed)
{
    setSize(sf::Vector2f(inNewWidth, Paddle_Length));
    setFillColor(sf::Color::Green);
    setPosition(sf::Vector2f(Paddle_Xpos, Paddle_Ypos));
}

Ball::Ball()
     : Velocity({Ball_VelocityX , Ball_VelocityY})
     , VelocityModifier(Ball_VelocityMod)
{
    setRadius(Ball_Radius);
    setFillColor(sf::Color::Yellow);
    setPosition(sf::Vector2f(Ball_Xpos, Ball_Ypos));
}

Grid::Grid()
{
    srand(time(nullptr));
    
    bricks.clear();
    bricks.resize(Grid_Length);
    for (auto& row : bricks)
    {
        row.resize(Grid_Width);
    }
    
    for (int i = 0; i < Grid_Length; i++)
    {
        for (int j = 0; j < Grid_Width; j++)
        {
            Brick brick;
            brick.IsCollided = rand() % 2;// randomized brick placements
            
            brick.setSize(sf::Vector2f(Brick_Width, Brick_Length));
            brick.setPosition({10.f + static_cast<float>(j) * (brick.getSize().x + 10.f), 10.f + static_cast<float>(i) * (brick.getSize().y + 10.f)});
            if (!brick.IsCollided)
            {
                brick.setFillColor(sf::Color(static_cast<uint8_t>(rand() % 255), static_cast<uint8_t>(rand() % 255), static_cast<uint8_t>(rand() % 255))); //active
            }
            else
            {
                brick.setFillColor(sf::Color::Transparent); // inactive - global bounds should not react to intersection
            }
    
            bricks[i][j] = brick;
        }
    }
}

LevelManager::LevelManager()
{
    if (!font.openFromFile(Score_Font))
    {
        std::cerr << "Unable to find " << Score_Font << "\n";
        return;
    }

    currScoreText.setFont(font);
    highScoreText.setFont(font);
}

bool LevelManager::StallBeforeGame(float deltaTime, float stallTime, sf::RenderWindow& inWindow, UIManager& outUIManager)
{
    stallTimer += deltaTime;
    if (stallTimer <= stallTime)
    {
        Update(inWindow, outUIManager);
        return  true;
    }

    return false;
}

void LevelManager::Update(RenderWindow& inWindow, UIManager& outUIManager)
{
    inWindow.clear();
    vector<bool> isClr;
    isClr.clear();
    for (vector<Brick>& bricks :grid.bricks)
    {
        for (Brick& brick : bricks)
        {
            isClr.emplace_back(brick.IsCollided);
            if (!brick.IsCollided) // if not marked as collided yet, draw because it is active
            {
                inWindow.draw(brick);
            }
        }
    }
        
    isLvClr = all_of(isClr.begin(), isClr.end(), // false if there is a single false in there
    [](bool outBool)
    {
        return outBool;
    });
    
    if (isLvClr)
    {
        outUIManager.SetLvClr();
        currentScore++;
        highestScore = max(currentScore, highestScore);
    }
    
    inWindow.draw(ball);
    inWindow.draw(paddle);
    inWindow.draw(currScoreText);
    inWindow.draw(highScoreText);
    inWindow.display();
}

void LevelManager::Reset()
{
    grid = Grid();
    paddle = Paddle();
    ball = Ball();
    stallTimer = 0.f;
    isLvClr = true;
}

void LevelManager::RestartCurrentLv(const Grid& inGridSnapshot)
{
    Reset();
    grid = inGridSnapshot;
}

void LevelManager::NextLv(float inPaddleWidth, float inBallVelMod)
{
    Reset();
    paddle = Paddle(inPaddleWidth, paddle.MoveSpeed * inBallVelMod); // move speed of paddle increase proportionally to ball velocity
    ball.VelocityModifier = inBallVelMod;
}

void LevelManager::writeHighestScoreToTxt(const string& inFileName)
{
    std::ofstream txtFile(inFileName, ios::trunc);
    if (!txtFile.is_open())
    {
        cerr << "Unable to write into " << inFileName << "\n";
        return;
    }
    
    txtFile << highestScore << "\n";
    txtFile.close();
}

void LevelManager::readHighestScoreFromTxt(const std::string& inFileName)
{
    std::ifstream txtFile(inFileName);

    if (!txtFile.is_open())
    {
        cerr << "Unable to read from " << inFileName << "\n";
        return;
    }
    
    txtFile >> highestScore;
    txtFile.close();
}

void LevelManager::SetupScoreboardText(EScoreType inScoreType, unsigned int inTextSize, const Color& inColor, const Vector2f& inPos)
{
    auto setup = [](Text& inText, unsigned int inTextSize, const Color& inColor, const Vector2f& inPos)
    {
        inText.setCharacterSize(inTextSize);
        inText.setFillColor(inColor);
        inText.setPosition(inPos);
    };
    
    switch (inScoreType)
    {
        case EScoreType::current:
        {
            setup(currScoreText, inTextSize, inColor, inPos);
        }
        break;
    case EScoreType::of_all_time:
        {
            setup(highScoreText, inTextSize, inColor, inPos);
        }
        break;
    }
}

void LevelManager::UpdateScoreboardText()
{
    currScoreText.setString("CLEARED: " + to_string(currentScore));
    highScoreText.setString("MOST CLEARED: " + to_string(highestScore));
}
