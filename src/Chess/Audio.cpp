#include "Chess/Audio.h"

Audio::Audio()
{
    m_MoveBuffer.loadFromFile("assets/sounds/move-self.wav");
    m_CaptureBuffer.loadFromFile("assets/sounds/capture.wav");

    m_MoveSound.setBuffer(m_MoveBuffer);
    m_CaptureSound.setBuffer(m_CaptureBuffer);
}

void Audio::PlayMoveSound()
{
    m_MoveSound.play();
}

void Audio::PlayCaptureSound()
{
    m_CaptureSound.play();
}