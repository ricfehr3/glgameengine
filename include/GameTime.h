#ifndef GAMETIME_H
#define GAMETIME_H

class GameApplication;

class GameTime
{
public:
    static float deltaTime;
private:
	friend GameApplication;
	static void init();
	static void updateDeltaTime();
	static uint64_t m_lastFrame;
	static uint64_t m_currentFrame;
	static constexpr float const& FRAMESPERSECOND = 1000000000.0f;
};

#endif