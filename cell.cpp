#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "cell.h"

/**
  Creates a new cell object at these x, and y coordinates
  @param x int x coordinate
  @param y int y coordinate
*/
Cell::Cell(const int x, const int y) {

  // randomly assigns a cell to alive or dead.
  int num = rand()%2;
  if (num == 1){
      this->is_alive_ = true;
      int r = 217;
      int g = 130;
      int b = 181;
      QColor c(r, g, b);
      this->color_ = c;
  }
  else {
      this->is_alive_ = false;
      int r = 255;
      int g = 255;
      int b = 255;
      QColor c(r, g, b);
      this->color_ = c;
  }

  x_ = x;
  y_ = y;

}

//in cell.cpp
/**
 * @brief Cell::mousePressEvent Track all types of mouse clicks. We'll use this to
 * keep track of what cells the user clicks.
 * @param event
 */
void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    qDebug() << "cell clicked! Coordinates of cell: " << x_ << "," << y_;

    if(event->button() == Qt::RightButton){
        // cell dies or remains dead, if already dead.
        emit CellSelectedDies(this);

        // Change cell colors to white.
        int r = 255;
        int g = 255;
        int b = 255;
        QColor c(r, g, b);
        color_ = c;

    }
    else if (event->button() == Qt::LeftButton){
        // Cell turns alive or stays alive, if already allive.
        emit CellSelectedLives(this);

        // Change cell colors to purple.
        int r = 217;
        int g = 130;
        int b = 181;
        QColor c(r, g, b);
        color_ = c;

    }

    // update cell to change color.
    update();
}

// where is this object located
// always a rectangle, Qt uses this to know "where" the user
// would be interacting with this object
QRectF Cell::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);
}

// define the actual shape of the object
QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, width_);
    return path;
}

// called by Qt to actually display the point
void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    // update the line for setBrush to be this
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
    painter->setBrush(b);
}

