#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define RECTANGLE_DENSITY 5.0f
#define RECTANGLE_FRICTION 0.2f
#define RECTANGLE_RESTITUTION 0.2f

#define barrier 1
#define enemy 2
class Rectangle : public GameItem
{
public:
    Rectangle(float x, float y, float w, float h,QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    int life=10000;
};

#endif // RECTANGLE_H
