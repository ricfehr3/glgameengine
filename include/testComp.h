#ifndef TESTCOMP_H
#define TESTCOMP_H

#include <GameComponent.h>
#include <GameObject.h>

class testComp : public GameComponent
{
public:
    testComp();
    void onRenderUpdate();
    
private:
    float x = 0.0f;
    float y = 0.0f;
};

#endif
