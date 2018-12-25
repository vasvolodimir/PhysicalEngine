#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QTimer>
#include <ctime>

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>

#include "window.h"
#include "physics.h"
#include "log.h"

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
        enum
        {
            Ellipse,
            Rectangle,
            Line
        };

public:
    void initModels();
    static Engine &instance(QObject *parent = 0);
    ~Engine();

    void createCenterItem(int type, QSize size, double mass, QBrush brush);
    /* Generate not intersected items */
    void generateItems(int type, unsigned count, QSize size, double mass,
                       QBrush brush);
    void handleMouseEvent(QMouseEvent *event);
    QTimer *createTimer(QObject *parent, QObject *handler,
                        const char *slot, int interval,
                        QTimer **timer);
    QGraphicsItem *createItem(int type, QRectF rect, QBrush brush);

private:
    QPointF getPos(QSize size) const;
    bool intersected(QRectF rect) const;
    QGraphicsEllipseItem *createEllipse(QRectF rect, QBrush brush);
    QGraphicsRectItem *createRect(QRectF rect, QBrush brush);
    QGraphicsLineItem *createLine(QRect rect, QBrush brush);

public slots:
        void gravityStep();

private:
        size_t m_width, m_height;
        QVector<Item*> m_items;
        int m_dt, m_eps;
        QObject *m_model;
};

#endif // ENGINE_H
