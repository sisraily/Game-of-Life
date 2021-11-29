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
Cell::Cell(const int x,const int y) {

  // randomly assigns a cell to have a 50 percent change of either being alive or dead.
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
  x_ = x*width_;
  y_ = y*width_;

}

//in cell.cpp
/**
 * Cell::mousePressEvent Track all types of mouse clicks. We'll use this to
 * keep track of what cells the user clicks. A right click kills a cell, while
 * a Left click makes it alive, if its dead.
 * @param event
 */
void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if(event->button() == Qt::RightButton){
        emit CellSelectedDies(this);
    }
    else if (event->button() == Qt::LeftButton){
        emit CellSelectedLives(this);
    }
    update();
}

// Location of cell. A rectangle.
QRectF Cell::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);
}

// Defines the shape of the cell.
QPainterPath Cell::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, width_);
    return path;
}

// Displays the cell
void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QBrush b = painter->brush();

    painter->setBrush(QBrush(color_));
    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
    painter->setBrush(b);
}


/*
 * When signal is called, this slot changes the color of the cell
 * to whichever button the user clicked.
 * @param color int 1 = Red, 2=Blue, 3=Green
*/
void Cell::CellColorChangeSlot(int color){

    if (this->is_alive()){
        switch(color)
        {
            case 1: {
                int r = 155;
                int g = 0;
                int b = 0;
                QColor c(r, g, b);
                this->color_ = c;
                break;
        }
            case (2):
        {
                int r = 0;
                int g = 155;
                int b = 0;
                QColor c(r, g, b);
                this->color_ = c;
                break;
        }

           case 3:
        {
                int r = 0;
                int g = 0;
                int b = 155;
                QColor c(r, g, b);
                this->color_ = c;
                break;
        }

    }
    }

}


/*
 * Slot changes the brightness of a cell based on how many cells are alive.
 * @param alpha a float value that sets the brightness, or opacity, of cell objects.
 */
void Cell::CellAlphaChangeSlot(float alpha){
    color_.setAlphaF(alpha);
    update();
}
