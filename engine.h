#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QTimer>
#include <ctime>

#include "window.h"
#include "physics.h"

class Window;

using namespace Physics;

class Engine : public QObject
{
    Q_OBJECT

    Engine(QObject *parent = 0);
    Engine(const QObject&);
    Engine &operator=(QObject&);

public:
    static Engine &instance(QObject *parent = 0);
    ~Engine();

    void createCenterEllipse(size_t length);
    void generateEllipses(unsigned count);
    void handle(QMouseEvent *event);

private:
    QPointF getPos(size_t length) const;
    bool intersected(QRectF rect) const;
    QGraphicsEllipseItem *createEllipse(QRectF rect, QColor brush);

private slots:
        void step();

private:
        size_t m_width, m_height;
        QVector<Ellipse*> m_ellipses;
        const int m_dt, m_eps;
        QTimer *m_timer;
};

#endif // ENGINE_H
