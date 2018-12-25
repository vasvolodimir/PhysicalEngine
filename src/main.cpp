#include "window.h"
#include "engine.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Window::instance();
    Engine::instance().initModels();

    return a.exec();
}
