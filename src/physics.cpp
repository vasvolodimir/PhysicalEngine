#include "physics.h"

double Physics::calcDistance(QPointF first, QPointF second)
{
    double part1 = (first.x() - second.x()) * (first.x() - second.x());
    double part2 = (first.y() - second.y()) * (first.y() - second.y());
    double answer = pow((part1 + part2), 0.5);

    return answer;
}
