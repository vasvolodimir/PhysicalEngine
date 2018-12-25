#include "centroid.h"

Centroid::Centroid(QObject *parent)
    : QObject(parent),
      m_timer(nullptr)
{
    Engine::instance().createCenterItem(QSize(20, 20), 20.0, Qt::white);
    Engine::instance().generateItems(100, QSize(5, 5), 2.0, Qt::black);

    Engine::instance().createTimer(this, &Engine::instance(),
                                   SLOT(gravityStep()), 20, &m_timer);
    m_timer->start();
}

Centroid::~Centroid()
{

}
