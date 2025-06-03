#pragma once

#include <SFML/Audio.hpp>
#include "Enums.hpp"

class SoundManager
{
    sf::SoundBuffer Ball_paddle_buffer = sf::SoundBuffer();
    sf::SoundBuffer Ball_brick_buffer = sf::SoundBuffer();

public:
    
    sf::Sound SetupSFX(ECollisionType inSoundType);
};

