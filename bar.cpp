#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "bar.h"

/**
  Creates a new cell object at these x, and y coordinates
  @param x int x coordinate
  @param y int y coordinate
*/
Bar::Bar(const int x, const int y, const int height) {
    x_ = x;
    y_ = y;
    // Assign and adjust height to coordinate system.
    height_ = height;
    QColor c(255, 255, 255);
    this->color_ = c;
}



// where is this object located
// always a rectangle, Qt uses this to know "where" the user
// would be interacting with this object
QRectF Bar::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

// define the actual shape of the object
QPainterPath Bar::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

// called by Qt to actually display the point
void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    // update the line for setBrush to be this
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->height_));
    painter->setBrush(b);
}
