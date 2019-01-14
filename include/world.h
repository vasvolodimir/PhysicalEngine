#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QTimer>

#include "engine.h"

class World : public QObject
{
    public:
            World(QObject *parent = 0);
            ~World();

    private:
            QTimer *m_timer;
};

#endif // WORLD_H
