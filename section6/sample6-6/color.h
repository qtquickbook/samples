#ifndef COLOR_H
#define COLOR_H

#include <QObject>
#include <QColor>

class Color : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor rgb MEMBER m_rgb NOTIFY rgbChanged)

public:
    explicit Color(QObject *parent = nullptr);
signals:

public slots:
};

#endif // COLOR_H
