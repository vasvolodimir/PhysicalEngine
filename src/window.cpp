#include "window.h"

Window::Window(QWidget *parent)
    : QGraphicsView(parent),
      m_scene(nullptr)
{
    QSize size = sizeHint();

    this->setWindowState(Qt::WindowFullScreen);
    this->resize(size);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setBackgroundBrush(Qt::white);

    createScene(this, &m_scene);

    this->show();
}

Window &Window::instance(QWidget *parent)
{
    static Window instance(parent);

    return instance;
}

Window::~Window()
{

}

QSize Window::sizeHint() const
{
    return QApplication::desktop()->size();
}

QGraphicsScene *Window::createScene(QWidget *parent, QGraphicsScene **scene)
{
    (*scene) = new QGraphicsScene(this->rect(), parent);

    if (scene)
        this->setScene(*scene);

    qDebug() << "View size: " << this->size();
    qDebug() << "Scene rect: " << this->rect();

    return *scene;
}


void Window::addItem(QGraphicsItem *item)
{
    m_scene->addItem(item);
}

QGraphicsScene *Window::getScene() const
{
    return m_scene;
}

void Window::mousePressEvent(QMouseEvent *event)
{
    Engine::instance().handleMouseEvent(event);
}
