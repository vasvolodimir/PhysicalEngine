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
        bool moveable;

        Ellipse(QGraphicsEllipseItem *item, double m, bool moveable)
            : item(item),
              x(item->x()),
              y(item->y()),
              m(m),
              moveable(moveable)
        { }
    };


    double calcDistance(QPointF first, QPointF second);
}

#endif // PHYSICS_H
