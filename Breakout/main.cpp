#include "LevelManager.hpp"
#include "UIManager.hpp"
#include "PhysicsManager.hpp"
#include "SoundManager.hpp"
#include "Constants.hpp"

using namespace std;
using namespace sf;

int main() // main game thread//entry point
{
    // initial window setup
    ContextSettings settings;
    RenderWindow window(VideoMode({window_width, window_length}),
        "Breakout", Style::Titlebar | Style::Close, State::Windowed, settings);
    window.setFramerateLimit(60);

    Clock clock;

    //Physics
    PhysicsManager physicsManager;
    
    //UI
    UIManager uiManager = UIManager(window);
    
    //SFX
    SoundManager soundManager;
    Sound paddleSound = soundManager.SetupSFX(ECollisionType::ball_paddle);
    Sound brickSound = soundManager.SetupSFX(ECollisionType::ball_bricks);
    
    //Level
    LevelManager lvManager;
   
    lvManager.currentScore = Initial_CurrentScore;
    if (!filesystem::exists(scoreTxtFile))
    {
        lvManager.writeHighestScoreToTxt(scoreTxtFile);
    }
    lvManager.readHighestScoreFromTxt(scoreTxtFile);
    lvManager.SetupScoreboardText(EScoreType::current, Scoreboard_TextSize, Color::White, Current_Score_During_Game_Pos);
    lvManager.SetupScoreboardText(EScoreType::of_all_time, Scoreboard_TextSize, Color::White, Highest_Score_During_Game_Pos);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (uiManager.GetGUI())
            {
                uiManager.GetGUI()->handleEvent(*event);
            }
            
            if (event->is<Event::Closed>())
                window.close();
        }
        
        float deltaTime = clock.restart().asSeconds(); // time passed since previous loop aka previous frame

        if (uiManager.GetGUIState() == EGUIState::quit || isKeyPressed(Keyboard::Key::Escape))
        {
            lvManager.writeHighestScoreToTxt(scoreTxtFile);
            return 0;
        }

        if (isKeyPressed(Keyboard::Key::P) || isKeyPressed(Keyboard::Key::Pause))
        {
            uiManager.SetPause();
        }

        uiManager.Update(window, lvManager);
        
        if (uiManager.GetGUIState() == EGUIState::start
            || uiManager.GetGUIState() == EGUIState::gameOver
            || uiManager.GetGUIState() == EGUIState::pause
            || uiManager.GetGUIState() == EGUIState::lvClr)
        {
            continue;
        }
        
        // update score texts in window
        lvManager.UpdateScoreboardText();
        
        if (lvManager.StallBeforeGame(deltaTime, stall_duration, window, uiManager))
        {
            continue;
        }

        // movements and collisions update
        physicsManager.MoveBall(deltaTime, window, lvManager.GetBall(), uiManager);
        physicsManager.MovePaddle(deltaTime, window, lvManager.GetPaddle());
        
        if (physicsManager.HandleCollision(ECollisionType::ball_paddle, lvManager)) // post physics collision detection should be better
        {
            /*lvManager.GetBall().Velocity.y *= -1.f;
                //only bounce the ball up if it is at the top of paddle
                //ball is considered left/right of paddle if paddle midx to ball midx is more than paddle midtoboundx
                //  if (std::fabs(paddleCenter.x - ballCenter.x) > (lvManager.GetPaddle().getSize().x / 2))
                //  {
                //      lvManager.GetBall().Velocity.y *= -1.f;
                //  }*/
            paddleSound.play();
        }
        else if (physicsManager.HandleCollision(ECollisionType::ball_bricks, lvManager))
        {
            brickSound.play();
        }

        lvManager.Update(window, uiManager);
    } // window while loop

    lvManager.writeHighestScoreToTxt(scoreTxtFile);
    return 0;
}

