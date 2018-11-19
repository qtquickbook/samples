#include "color.h"

Color::Color(QObject *parent) : QObject(parent)
{

}

void Color::black()
{
    m_rgb = QColor("#000000");
    emit rgbChanged(m_rgb);
}
