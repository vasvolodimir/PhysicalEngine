#ifndef PHYSICS_H
#define PHYSICS_H

#include <QRect>
#include <QGraphicsEllipseItem>
#include <cmath>

#define G 0.067

namespace Physics
{
    struct Ellipse
    {
        QGraphicsEllipseItem *item;
        double x, y;
        double vx = 0, vy = 0;
        double m;
        bool move;

        Ellipse(QGraphicsEllipseItem *item, double m, bool move)
            : item(item),
              x(item->x()),
              y(item->y()),
              m(m),
              move(move)
        { }
    };


    double calcDistance(QPointF first, QPointF second);
}

#endif // PHYSICS_H
