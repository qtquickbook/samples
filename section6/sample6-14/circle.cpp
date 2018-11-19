#include "circle.h"

Circle::Circle(QQuickItem *parent) : QQuickPaintedItem(parent)
{

}

void Circle::paint(QPainter *painter)
{
    painter->drawEllipse(x(), y(), width(), height());
}
