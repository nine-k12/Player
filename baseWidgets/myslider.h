#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QWidget>
#include <QMouseEvent>
#include <QSlider>

class mySlider: public QSlider
{
    Q_OBJECT
public:
    explicit mySlider(QWidget* parent=nullptr);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    QPoint m_curPoint;
    void getCurPoint(QMouseEvent* event);
};

#endif // MYSLIDER_H
