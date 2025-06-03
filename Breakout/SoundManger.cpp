#include <iostream>

#include "SoundManager.hpp"
#include "Constants.hpp"

using namespace std;

sf::Sound SoundManager::SetupSFX(ECollisionType inSoundType)
{
  switch (inSoundType)
  {
    case ECollisionType::ball_paddle:
      {
        if (!Ball_paddle_buffer.loadFromFile(ball_paddle_sfx))
        {
          std::cerr << "Unable to load SFX file" << ball_paddle_sfx << "\n";
        }
        
        return sf::Sound(Ball_paddle_buffer); // should have RVO here
      }
    
    case ECollisionType::ball_bricks:
      {
        if (!Ball_brick_buffer.loadFromFile(ball_brick_sfx))
        {
          std::cerr << "Unable to load SFX file" << ball_brick_sfx << "\n";
        }
        
        return sf::Sound(Ball_brick_buffer); // should have RVO here
      }
  }
}
