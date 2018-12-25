#ifndef CENTROID_H
#define CENTROID_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include "engine.h"

class Centroid : public QObject
{
    Q_OBJECT

    public:
        Centroid(QObject *parent = 0);
        ~Centroid();

    private:
            QTimer *m_timer;
};

#endif // CENTROID_H
