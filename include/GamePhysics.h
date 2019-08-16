#ifndef GAMEPHYSICS_H
#define GAMEPHYSICS_H

class btBroadphaseInterface;
class btCollisionDispatcher;
class btConstraintSolver;
class btDefaultCollisionConfiguration;
class btDiscreteDynamicsWorld;

class GamePhysics
{
public:
	GamePhysics();
	void init();

private:
	btBroadphaseInterface* m_pBroadphase;
	btCollisionDispatcher* m_pDispatcher;
	btConstraintSolver* m_pSolver;
	btDefaultCollisionConfiguration* m_pCollisionConfiguration;
	btDiscreteDynamicsWorld* m_pDynamicsWorld;
};

#endif