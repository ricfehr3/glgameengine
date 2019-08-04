#include <GameScene.h>

GameScene::GameScene(std::string sceneName)
{
    m_name = sceneName;
}

std::string GameScene::getName(std::string)
{
    return m_name;
}

void GameScene::setActive()
{

}

void GameScene::disable()
{

}
