#pragma once
#include <cstdint>


enum class ECollisionType : uint8_t
{
    ball_paddle,
    ball_bricks,
};

enum class EShapeType : uint8_t
{
    paddle,
    ball,
};

enum class EGUIState : uint8_t
{
    game,
    restart,
    start,
    pause,
    gameOver,
    lvClr,
    nxtLv,
    win,
    quit,
};

enum class EScoreType : uint8_t
{
    current,
    of_all_time,
};
