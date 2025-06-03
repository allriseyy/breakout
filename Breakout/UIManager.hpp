#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "Enums.hpp"
#include "LevelManager.hpp"

class LevelManager;

class UIManager
{
public:
    
    UIManager(sf::RenderWindow& inWindow);
    ~UIManager();

    tgui::Gui* GetGUI() const { return GUI; }
    const EGUIState GetGUIState() const { return CurrentState; }
    void SetupStart();
    void SetupGameOver();
    void SetupPause();
    void SetupLvClr();
    void SetupScoreboard(const LevelManager& inLvManager);

    void Update(sf::RenderWindow& inWindow, LevelManager& outLvManager);
    void SetLvClr() { CurrentState = EGUIState::lvClr; }
    void SetGameOver() { CurrentState = EGUIState::gameOver; }
    void SetPause() { CurrentState = EGUIState::pause; }

private:

    EGUIState CurrentState = EGUIState::start;
    tgui::Gui* GUI = nullptr;
    Grid gridSnapshot; // snapshot of specific grid layout and color at the start of every new level - for the purpose of current level restart
    
    void AddRestartButton(const tgui::Layout2d& inPos, const tgui::Layout2d& inSize);
    void AddBackToStartButton(const tgui::Layout2d& inPos, const tgui::Layout2d& inSize);
    void AddQuitButton(const tgui::Layout2d& inPos, const tgui::Layout2d& inSize);
    
    tgui::Button::Ptr MakeButton(const std::string& inButtonText, const tgui::Layout2d& inPos, const tgui::Layout2d& inSize);
    tgui::Label::Ptr MakeText(const std::string& inButtonText, const tgui::Layout2d& inPos, unsigned int inSize);
    
};
