#pragma once
#include <TGUI/TGUI.hpp>

constexpr unsigned int window_width = 800;
constexpr unsigned int window_length = 600;
constexpr float stall_duration = 1.f;
const std::string scoreTxtFile = "Score.txt";
constexpr uint8_t Initial_CurrentScore = 0;
constexpr unsigned int Scoreboard_TextSize = 18;
constexpr sf::Vector2f Current_Score_During_Game_Pos = sf::Vector2f(200.f, 550.f);
constexpr sf::Vector2f Highest_Score_During_Game_Pos = sf::Vector2f(400.f, 550.f);

const std::string start_button = "START";
const std::string restart_button = "RESTART LV";
const std::string quit_button = "QUIT";
const std::string backToStart_button = "MAIN MENU";
const std::string resume_button = "RESUME";
const std::string nxtLv_button = "NEXT";
const tgui::Layout2d Button_Size = tgui::Layout2d(150,25);
constexpr float Paddle_Width_Min_Cap = 30.f;
constexpr float Paddle_Width_Downscale_Rate = 0.9f;
constexpr float Ball_VelMod_Max_Cap = 5.f;
constexpr float Ball_VelMod_Upscale_Rate = 1.1f;

const std::string gameOver_label = "GAME OVER :(";
const std::string cleared_label = "LEVEL CLEARED!";
const std::string title_label = "BREAKOUT?";
const std::string paused_label = "PAUSED";

const std::string Score_Font = "ComicRelief-Regular.ttf";
constexpr float Paddle_Xpos = 350.f;
constexpr float Paddle_Ypos = 500.f;
constexpr float Paddle_Speed = 650.f;
constexpr float Paddle_Width = 150.f;
constexpr float Paddle_Length = 10.f;
constexpr float Ball_Radius = 8.f;
constexpr float Ball_VelocityX = 350.f;
constexpr float Ball_VelocityY = 380.f;
constexpr float Ball_VelocityMod = 1.f;
constexpr float Ball_Xpos = 320.f;
constexpr float Ball_Ypos = 250.f;
constexpr int Grid_Width = 9;
constexpr int Grid_Length = 4;
constexpr float Brick_Width = 78.f;
constexpr float Brick_Length = 50.f;

const std::string ball_paddle_sfx = "ball_paddle.wav";
const std::string ball_brick_sfx = "ball_brick.wav";