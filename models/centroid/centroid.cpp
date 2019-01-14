#include "centroid.h"

Centroid::Centroid(QObject *parent)
    : QObject(parent),
      m_timer(nullptr)
{
    Engine::instance().createCenterItem(Engine::Ellipse, QSize(20, 20), 20.0,
                                        Qt::white, false);
    Engine::instance().generateItems(Engine::Ellipse, 100, QSize(5, 5),
                                     2.0, Qt::black);

    Engine::instance().createTimer(this, &Engine::instance(),
                                   SLOT(globalGravityStep()), 20, &m_timer);
    m_timer->start();
}

Centroid::~Centroid()
{

}
