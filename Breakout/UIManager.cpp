#include "UIManager.hpp"
#include "LevelManager.hpp"
#include "Constants.hpp"

using namespace std;
using namespace tgui;
using namespace sf;

UIManager::UIManager(sf::RenderWindow& inWindow)
{
    GUI = new Gui(inWindow);
    CurrentState = EGUIState::start;
}

UIManager::~UIManager()
{
    delete GUI;
    GUI = nullptr;
}

void UIManager::SetupStart()
{
    if (!GUI->get(title_label))
    {
        MakeText(title_label, Layout2d(225,225), 60);
    }
    
    if (! GUI->get(start_button))
    {
        Button::Ptr start = MakeButton(start_button, Layout2d(200,500), Button_Size);
        start->onClick([this]()
        {
            CurrentState = EGUIState::game;
            GUI->removeAllWidgets();
        });
    }
    
    AddQuitButton(Layout2d(400,500),Button_Size);
}

void UIManager::SetupGameOver()
{
    if (!GUI->get(gameOver_label))
    {
        MakeText(gameOver_label, Layout2d(100,100), 24);
    }
    
    AddBackToStartButton(Layout2d(100,300), Button_Size);
    AddQuitButton(Layout2d(100,500),Button_Size);
}

void UIManager::SetupPause()
{
    if (!GUI->get(paused_label))
    {
        MakeText(paused_label, Layout2d(100,100), 24);
    }
    
    if (!GUI->get(resume_button))
    {
        Button::Ptr resume = MakeButton(resume_button, Layout2d(400,300), Button_Size);
        resume->onClick([this]()
        {
            CurrentState = EGUIState::game;
            GUI->removeAllWidgets();
        });
    }

    AddRestartButton(Layout2d(100,400), Button_Size);
    AddBackToStartButton(Layout2d(100,300), Button_Size);
    AddQuitButton(Layout2d(100,500), Button_Size);
}

void UIManager::SetupLvClr()
{
    if (!GUI->get("LEVEL CLEARED!"))
    {
        MakeText("LEVEL CLEARED!", Layout2d(100,100), 24);
    }
    if (!GUI->get(nxtLv_button))
    {
        Button::Ptr nextLv = MakeButton(nxtLv_button, Layout2d(400,500), Button_Size);
        nextLv->onClick([this]()
        {
            CurrentState = EGUIState::nxtLv;
            GUI->removeAllWidgets();
        });
    }
    
    AddRestartButton(Layout2d(100,400), Button_Size);
    AddBackToStartButton(Layout2d(100,300), Button_Size);
    AddQuitButton(Layout2d(100,500), Button_Size);
}

void UIManager::SetupScoreboard(const LevelManager& inLvManager)
{
    string titleString = "CLEARED:";
    string current = to_string(inLvManager.currentScore);
    if (!GUI->get(titleString + current))
    {
        MakeText(titleString + current, Layout2d(350,0), 24);
    }
    
    string titleString2 = "MOST CLEARED:";
    string highest = to_string(inLvManager.highestScore);
    if (!GUI->get(titleString2 + highest))
    {
        MakeText(titleString2 + highest, Layout2d(550,0), 24);
    }
}

void UIManager::Update(RenderWindow& inWindow, LevelManager& outLvManager)
{
        if (CurrentState == EGUIState::start)
        {
            SetupStart();
            outLvManager.currentScore = 0;
            SetupScoreboard(outLvManager);
            outLvManager.Reset();
            gridSnapshot = outLvManager.GrabGridSnapshot();
            inWindow.clear();
            GetGUI()->draw();
            inWindow.display();
            return;
        }
        if ((CurrentState == EGUIState::gameOver))
        {
            SetupGameOver();
            SetupScoreboard(outLvManager);
            inWindow.clear();
            GetGUI()->draw();
            inWindow.display();
            return;
        }
        if (CurrentState == EGUIState::restart)
        {
            if (outLvManager.isLvClr) // must do this before restarting current level
            {
                outLvManager.currentScore--; // undo the score count when restarting a cleared level
            }
            outLvManager.RestartCurrentLv(gridSnapshot);
            CurrentState = EGUIState::game;
        }
        if (CurrentState == EGUIState::pause)
        {
            SetupPause();
            SetupScoreboard(outLvManager);
            inWindow.clear();
            GetGUI()->draw();
            outLvManager.ResetStallTimer();
            inWindow.display();
            return;
        }
        if (CurrentState == EGUIState::lvClr)
        {
            SetupLvClr();
            SetupScoreboard(outLvManager);
            inWindow.clear();
            GetGUI()->draw();
            inWindow.display();
            return;
        }
        if (CurrentState == EGUIState::nxtLv)
        {
            float newPaddleWidth =
                (outLvManager.GetPaddle().getSize().x * Paddle_Width_Downscale_Rate < Paddle_Width_Min_Cap)
                    ? Paddle_Width_Min_Cap : outLvManager.GetPaddle().getSize().x * Paddle_Width_Downscale_Rate;
            
            float newBallVelMod =
                (outLvManager.GetBall().VelocityModifier * Ball_VelMod_Upscale_Rate > Ball_VelMod_Max_Cap)
                    ? Ball_VelMod_Max_Cap : outLvManager.GetBall().VelocityModifier * Ball_VelMod_Upscale_Rate;
            
            outLvManager.NextLv(newPaddleWidth, newBallVelMod);
            gridSnapshot = outLvManager.GrabGridSnapshot();
            CurrentState = EGUIState::game;
        }
}

Button::Ptr UIManager::MakeButton(const string& inButtonText, const Layout2d& inPos, const Layout2d& inSize)
{
    Button::Ptr button = Button::create(inButtonText);
    button->setPosition(inPos.x, inPos.y);
    button->setSize(inSize.x, inSize.y);
    GUI->add(button,inButtonText);
    return button;
}

Label::Ptr UIManager::MakeText(const string& inButtonText, const Layout2d& inPos, unsigned int inSize)
{
    Label::Ptr label = Label::create();
    label->setText(inButtonText);
    label->setPosition(inPos.x, inPos.y);
    label->setTextSize(inSize);
    label->getRenderer()->setTextColor(tgui::Color::White);
    GUI->add(label, inButtonText);
    return label;
}

void UIManager::AddRestartButton(const Layout2d& inPos, const Layout2d& inSize)
{
    if (!GUI->get(restart_button))
    {
        Button::Ptr restart = MakeButton(restart_button, inPos, inSize);
        restart->onClick([this]()
        {
            CurrentState = EGUIState::restart;
            GUI->removeAllWidgets();
        });
    }
}

void UIManager::AddBackToStartButton(const Layout2d& inPos, const Layout2d& inSize)
{
    if (!GUI->get(backToStart_button))
    {
        Button::Ptr BackToStart = MakeButton(backToStart_button, inPos, inSize);
        BackToStart->onClick([this]()
        {
            CurrentState = EGUIState::start;
            GUI->removeAllWidgets();
        });
    }
}

void UIManager::AddQuitButton(const Layout2d& inPos, const Layout2d& inSize)
{
    if (!GUI->get(quit_button))
    {
        Button::Ptr quit = MakeButton(quit_button, inPos, inSize);
        quit->onClick([this]()
        {
           CurrentState = EGUIState::quit;
            GUI->removeAllWidgets();
        });
    }
}
