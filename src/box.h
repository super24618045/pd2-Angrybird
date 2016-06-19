#ifndef BOX_H
#define BOX_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BOX_DENSITY 20.0f
#define BOX_FRICTION 0.2f
#define BOX_RESTITUTION 0.2f

class Box : public GameItem
{
public:
    Box(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};
#endif // BOX_H
