#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <ctime>

#include "window.h"
#include "physics.h"

#ifdef CONFIG_CENTROID_MODEL
#include "centroid.h"
#endif

class Window;

using namespace Physics;

class Engine : public QObject
{
    Q_OBJECT

    Engine(QObject *parent = 0);
    Engine(const QObject&);
    Engine &operator=(QObject&);

public:
    void initModels();
    static Engine &instance(QObject *parent = 0);
    ~Engine();

    void createCenterItem(QSize size, double mass, QBrush brush);
    /* Generate not intersected items */
    void generateItems(unsigned count, QSize size, double mass, QBrush brush);
    void handleMouseEvent(QMouseEvent *event);
    QTimer *createTimer(QObject *parent, QObject *handler,
                        const char *slot, int interval,
                        QTimer **timer);

private:
    QPointF getPos(QSize size) const;
    bool intersected(QRectF rect) const;
    QGraphicsEllipseItem *createEllipse(QRectF rect, QBrush brush);

public slots:
        void gravityStep();

private:
        size_t m_width, m_height;
        QVector<Item*> m_items;
        QGraphicsItem *m_center;
        int m_dt, m_eps;
        QObject *m_model;
};

#endif // ENGINE_H
