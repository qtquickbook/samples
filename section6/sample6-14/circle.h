#ifndef CIRCLE_H
#define CIRCLE_H

#include <QQuickPaintedItem>
#include <QPainter>

class Circle : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit Circle(QQuickItem *parent = nullptr);
    void paint(QPainter *painter);

signals:

public slots:
};

#endif // CIRCLE_H
