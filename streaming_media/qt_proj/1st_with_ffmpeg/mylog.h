
#ifndef MYLOG_H
#define MYLOG_H

#include <QDateTime>
#include <QDebug>

#define LOG \
  qDebug().nospace() << '[' << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz") \
                     << __FILE__ << ':' << __LINE__ << ':' << __func__ << "()] "

#endif // MYLOG_H
