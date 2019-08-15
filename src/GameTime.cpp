#include <SDL2/SDL.h>

#include "GameTime.h"
#include "GameApplication.h"

void GameTime::init()
{
	m_lastFrame = SDL_GetPerformanceCounter();
}

void GameTime::updateDeltaTime()
{
	m_currentFrame = SDL_GetPerformanceCounter();
	uint64_t framesElapsed = m_currentFrame - m_lastFrame;
	deltaTime = (float)(framesElapsed / FRAMESPERSECOND);
	m_lastFrame = m_currentFrame;
}

float GameTime::deltaTime = 0.0f;
uint64_t GameTime::m_lastFrame = 0;
uint64_t GameTime::m_currentFrame = 0;