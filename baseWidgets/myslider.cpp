#include "myslider.h"

#include <QPainter>

mySlider::mySlider(QWidget* parent):
    QSlider(parent){
    m_curPoint = QPoint(0, 0);
}

void mySlider::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.setBrush(QColor(255, 0, 0));
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRoundedRect(QRect(0, this->height()/5*2, m_curPoint.x(),
                                      this->height()/5), 4, 4);

    painter.setBrush(QColor(206, 206, 206));
        painter.drawRoundedRect(QRect(m_curPoint.x(), this->height()/5*2, this->width()-m_curPoint.x(),
                                      this->height()/5), 4, 4);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(206, 206, 206));
}

void mySlider::mousePressEvent(QMouseEvent *event)
{
    getCurPoint(event);
}

void mySlider::mouseMoveEvent(QMouseEvent *event)
{
    getCurPoint(event);
}

void mySlider::getCurPoint(QMouseEvent *event)
{
    if(event->pos().x() == 0){
        m_curPoint = QPoint(0, 0);
    }
    else if(event->pos().x() > this->width()){
        m_curPoint = QPoint(this->width(), 0);
    }
    else{
        m_curPoint = event->pos();
    }
    setValue(m_curPoint.x());
    update();

    int m_curVal = (int)(m_curPoint.x())/(this->width())*100;
    emit valueChanged(m_curVal);
}

