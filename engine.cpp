#include "engine.h"

Engine::Engine(QObject *parent)
    : QObject(parent),
      m_width(0),
      m_height(0),
      m_ellipses(0),
      m_dt(20),
      m_eps(0.1),
      m_timer(nullptr)
{
    m_width = Window::instance().getScene()->width();
    m_height = Window::instance().getScene()->height();

    createCenterEllipse(20);
    generateEllipses(100);

    m_timer = new QTimer(this);
    m_timer->setInterval(m_dt);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(step()));
    m_timer->start();

    step();
}

Engine &Engine::instance(QObject *parent)
{
    static Engine instance(parent);

    return instance;
}

Engine::~Engine()
{

}

void Engine::createCenterEllipse(size_t length)
{
    QGraphicsEllipseItem *item;

    item = createEllipse(QRectF(0, 0, length, length), Qt::white);
    item->setPos((m_width - length) / 2, (m_height - length) / 2);

    m_ellipses.push_back(new Ellipse(item, 20.0, false)); // XXX: Change mass
    Window::instance().addItem(item);
}

QGraphicsEllipseItem *Engine::createEllipse(QRectF rect, QColor brush)
{
    QGraphicsEllipseItem *item = new QGraphicsEllipseItem(rect);
    item->setBrush(brush);
    item->setPen(Qt::NoPen);

    return item;
}

void Engine::generateEllipses(unsigned count)
{
    QGraphicsEllipseItem *item;
    size_t length = 5;

    for(unsigned i=0; i<count; i++)
    {
        item = createEllipse(QRectF(0, 0, length, length), Qt::black);
        item->setPos(getPos(length));
        m_ellipses.push_back(new Ellipse(item, rand() % 5 + 1, true)); // XXX: Change mass
        Window::instance().addItem(item);
    }
}

void Engine::handle(QMouseEvent *event)
{
    m_ellipses[0]->item->setPos(event->x(), event->y());

    for(int i=1; i<m_ellipses.size(); i++)
    {
        m_ellipses[i]->moveable = true;
        m_ellipses[i]->vx = 0;
        m_ellipses[i]->vy = 0;
    }
}

QPointF Engine::getPos(size_t length) const
{
    double x, y;
    QRectF rect;

    srand(time(NULL));

    do {
        x = length + rand() % m_width - length; // Ellipse will be inbound of scene
        y = length + rand() % m_height - length;
        rect.setRect(x, y, length, length);

    } while (intersected(rect));

    return QPointF(x, y);
}

bool Engine::intersected(QRectF rect) const
{
    if (m_ellipses.isEmpty())
        return false;

    for(int i=0; i<m_ellipses.size(); i++)
    {
        QRectF ellipse;

        ellipse.setRect(m_ellipses[i]->item->scenePos().x(),
                        m_ellipses[i]->item->scenePos().y(),
                        m_ellipses[i]->item->rect().width(),
                        m_ellipses[i]->item->rect().height());

        if (rect.intersects(ellipse))
            return true;
    }

    return false;
}

void Engine::step()
{
    double dx, dy, r, a, ax, ay;
    int center = 0;

    for(int i=0; i<m_ellipses.size(); i++)
        {
            if (i == center || !m_ellipses[i]->moveable)
                continue;

            dx = m_ellipses[center]->item->x() - m_ellipses[i]->item->x();
            dy = m_ellipses[center]->item->y() - m_ellipses[i]->item->y();
            r = calcDistance(m_ellipses[center]->item->pos(), m_ellipses[i]->item->pos());

            /* XXX: This case added manually to avoid colliding bugs */
            if (r > 50 || !m_ellipses[i]->vx || !m_ellipses[i]->vy)
            {
                a = G * m_ellipses[center]->m / pow(r, 2);
                ax = a * dx / r; // a * cos
                ay = a * dy / r; // a * sin

                m_ellipses[i]->vx += ax * m_dt;
                m_ellipses[i]->vy += ay * m_dt;
            }

            if (m_ellipses[i]->moveable)
            {
                m_ellipses[i]->item->setX(m_ellipses[i]->item->x() +
                                          m_ellipses[i]->vx * m_dt);
                m_ellipses[i]->item->setY(m_ellipses[i]->item->y() +
                                          m_ellipses[i]->vy * m_dt);
            }

            if (m_ellipses[i]->item->collidesWithItem(m_ellipses[center]->item))
                m_ellipses[i]->moveable = false;
        }
}
