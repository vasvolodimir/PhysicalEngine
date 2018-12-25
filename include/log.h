#ifndef LOG_H
#define LOG_H

#include <QDebug>

#define LOG_D(str) qDebug() << __FILE__ << ":" << __LINE__ << ":" << str;

#endif // LOG_H
