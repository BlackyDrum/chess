#pragma once

#include "SFML/Audio.hpp"

class Audio
{
public:
    Audio();

    void PlayMoveSound();
    void PlayCaptureSound();
private:
    sf::SoundBuffer m_MoveBuffer;
    sf::Sound m_MoveSound;

    sf::SoundBuffer m_CaptureBuffer;
    sf::Sound m_CaptureSound;
};