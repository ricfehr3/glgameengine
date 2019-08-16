#include <bullet/btBulletDynamicsCommon.h>

#include <GamePhysics.h>

GamePhysics::GamePhysics()
{
	
}

void GamePhysics::init()
{
	m_pBroadphase = new btDbvtBroadphase();
	m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
	m_pSolver = new btSequentialImpulseConstraintSolver();
	m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
	m_pDynamicsWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);
}