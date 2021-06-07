#include "logowidget.h"
#include <QPainter>

LogoWidget::LogoWidget(QWidget *parent) : QWidget(parent)
{

}

void LogoWidget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    p.setBrush(Qt::blue);
    p.drawRect(0, 0, 200, 200);

    QPen pen(Qt::green, 2, Qt::DotLine);
    p.setPen(pen);
    p.drawRect(10, 10, 180, 180);

    p.setPen(Qt::red);
    p.setBrush(Qt::red);
    p.drawEllipse(25, 25, 150, 150);

    QFont font;
    font.setItalic(true);
    font.setPointSize(20);
    p.setFont(font);
    p.setPen(Qt::white);
    p.drawText(50, 100, "carsfilter");
}
