#include <testComp.h>
#include <GameComponentManager.h>
#include <cmath>

testComp::testComp()
{
    m_name = "testMoveComponent";    
    //ObjectRegistryManager<GameComponent>::ObjectRegistration(this);
    //GameComponentManager::ObjectRegistration(this);
}

void testComp::onRenderUpdate()
{
    //mp_gameObject->setPosition(glm::vec3(sin(x), -1.8f, cos(y)));
    //mp_gameObject->setEulerRotation(glm::vec3(0.0f, x*50, 0.0f));
    mp_gameObject->setScale(glm::vec3(sin(x)*.1+.2, sin(x)*.1+.2, sin(x)*.1+.2));
    x += 0.001;
    y += 0.001;
}


auto registertestComp = []
{
    GameComponentManager::RegisterObject<testComp>();
    return NULL;
}();

