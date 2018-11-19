#ifndef COLOR_H
#define COLOR_H

#include <QObject>

class Color : public QObject
{
    Q_OBJECT
public:
    explicit Color(QObject *parent = nullptr);

signals:

public slots:
};

#endif // COLOR_H