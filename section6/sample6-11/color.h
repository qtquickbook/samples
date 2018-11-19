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
    void rgbChanged(QColor rgb);

public slots:
    void black();

private:
    QColor m_rgb;
};

#endif // COLOR_H
