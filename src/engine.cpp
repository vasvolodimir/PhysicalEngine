#include "engine.h"

Engine::Engine(QObject *parent)
    : QObject(parent),
      m_width(0),
      m_height(0),
      m_items(0),
      m_center(nullptr),
      m_dt(20),
      m_eps(0.1),
      m_model(nullptr)
{
    m_width = Window::instance().getScene()->width();
    m_height = Window::instance().getScene()->height();
}

Engine &Engine::instance(QObject *parent)
{
    static Engine instance(parent);

    return instance;
}

Engine::~Engine()
{
    if (m_model)
        delete m_model;
}

void Engine::createCenterItem(QSize size, double mass, QBrush brush)
{
    m_center = createEllipse(QRectF(0, 0, size.width(), size.height()), brush);
    m_center->setPos((m_width - size.width()) / 2, (m_height - size.height()) / 2);

    m_items.push_back(new Item(m_center, mass, false)); // XXX: Change mass
    Window::instance().addItem(m_center);
}

QGraphicsEllipseItem *Engine::createEllipse(QRectF rect, QBrush brush)
{
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(rect);
    item->setBrush(brush);
    item->setPen(Qt::NoPen);

    return item;
}

QTimer *Engine::createTimer(QObject *parent, QObject *handler,
                            const char *slot, int interval,
                            QTimer **timer)
{
    if (!parent || !handler || !slot)
        return nullptr;

    (*timer) = new QTimer(parent);
    (*timer)->setInterval(interval);
    m_dt = interval;

    connect(*timer, SIGNAL(timeout()), handler, slot);

    return *timer;
}

void Engine::initModels()
{
#ifdef CONFIG_CENTROID_MODEL
    m_model = new Centroid(this);
#endif
}

void Engine::generateItems(unsigned count, QSize size, double mass,
                           QBrush brush)
{
    QGraphicsItem *item;

    for(unsigned i=0; i<count; i++)
    {
        item = createEllipse(QRectF(0, 0, size.width(),
                                    size.height()), brush);
        item->setPos(getPos(size));
        m_items.push_back(new Item(item, mass, true));
        Window::instance().addItem(item);
    }
}

void Engine::handleMouseEvent(QMouseEvent *event)
{

}

QPointF Engine::getPos(QSize size) const
{
    double x, y;
    QRectF rect;

    srand(time(NULL));

    do {
        x = size.width() + rand() % m_width - size.width();
        y = size.height() + rand() % m_height - size.height();
        rect.setRect(x, y, size.width(), size.height());

    } while (intersected(rect));

    return QPointF(x, y);
}

bool Engine::intersected(QRectF rect) const
{
    QRectF ellipse;
    QGraphicsEllipseItem *item;

    if (m_items.isEmpty())
        return false;

    for(int i=0; i<m_items.size(); i++)
    {
        item = dynamic_cast<QGraphicsEllipseItem*> (m_items[i]->item);

        if (!item)
        {
            Q_ASSERT("Cast error!");
            return false;
        }

        ellipse.setRect(item->scenePos().x(),
                        item->scenePos().y(),
                        item->rect().width(),
                        item->rect().height());

        if (rect.intersects(ellipse))
            return true;
    }

    return false;
}

void Engine::gravityStep()
{
    double dx, dy, r, a, ax, ay;
    int center = 0;

    for(int i=0; i<m_items.size(); i++)
        {
            if (i == center || !m_items[i]->moveable)
                continue;

            dx = m_items[center]->item->x() - m_items[i]->item->x();
            dy = m_items[center]->item->y() - m_items[i]->item->y();
            r = calcDistance(m_items[center]->item->pos(), m_items[i]->item->pos());

            /* XXX: This case added manually to avoid colliding bugs */
            if (r > 50 || !m_items[i]->vx || !m_items[i]->vy)
            {
                a = G * m_items[center]->m / pow(r, 2);
                ax = a * dx / r; // a * cos
                ay = a * dy / r; // a * sin

                m_items[i]->vx += ax * m_dt;
                m_items[i]->vy += ay * m_dt;
            }

            if (m_items[i]->moveable)
            {
                m_items[i]->item->setX(m_items[i]->item->x() +
                                          m_items[i]->vx * m_dt);
                m_items[i]->item->setY(m_items[i]->item->y() +
                                          m_items[i]->vy * m_dt);
            }

            if (m_items[i]->item->collidesWithItem(m_items[center]->item))
                m_items[i]->moveable = false;
        }
}
