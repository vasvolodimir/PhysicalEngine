#ifndef PHYSICS_H
#define PHYSICS_H

#include <QRect>
#include <QGraphicsEllipseItem>
#include <cmath>

#define G 0.067
#define NEWTON_G 9.8

namespace Physics
{
    struct Item
    {
        QGraphicsItem *item;
        double x, y;
        double vx = 0, vy = 0;
        double m;
        bool moveable;

        Item(QGraphicsItem *item, double m, bool moveable)
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
