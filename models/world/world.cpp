#include "world.h"

World::World(QObject *parent)
    : QObject(parent),
      m_timer(nullptr)
{
       Engine::instance().createGround();
       Engine::instance().createCenterItem(Engine::Rectangle, QSize(20, 20),
                                           2.0, Qt::darkGreen, true);
       Engine::instance().createTimer(this, &Engine::instance(),
                                      SLOT(verticalMove()), 1000, &m_timer);
       m_timer->start();
}

World::~World()
{

}


